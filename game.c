#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "map.h"
#include "utils.h"

int main_menu(void)
{
    int selection;
    while (1) {
        printf("Select difficulty:\n"
               "1 - Easy\n"
               "2 - Medium\n"
               "3 - Hard\n"
               "4 - Quit\n");
        if (scanf("%d", &selection) != 1) {
            clear_buffer();
            refresh_screen();
            printf("Invalid input! Please enter a number.\n\n");
            continue;
        }

        switch (selection) {
            case 1:
            case 2:
            case 3:
                return selection;
            case 4:
                return 0;
            default:
                refresh_screen();
                printf("Invalid selection! Please choose 1-4.\n\n");
                clear_buffer();
        }
    }
}

void gameplay(int n, char **map, BombConfig config)
{
    int **fog = generate_fog(n);
    if (!fog) {
        fprintf(stderr, "Memory allocation for fog failed.\n");
        return;
    }

    int bombs = (n == 10) ? config.easy :
                (n == 18) ? config.medium :
                            config.hard;

    int x, y;
    int revealed = 0;
    int playing = 1;

    while (playing) {
        display_map(n, map, fog, 0);
        printf("Enter coordinates (x y): ");
        if (scanf("%d %d", &x, &y) != 2 || x < 1 || y < 1 || x > n - 2 || y > n - 2) {
            refresh_screen();
            printf("Invalid coordinates! Please try again.\n");
            clear_buffer();
            continue;
        }

        if (fog[x][y]) {
            refresh_screen();
            printf("Cell already uncovered! Try a different one.\n");
            continue;
        }

        if (map[x][y] == 'b') {
            refresh_screen();
            display_map(n, map, fog, 1); // reveal all
            printf("BOOM! You hit a bomb at (%d, %d).\n", x, y);
            break;
        }

        fill(map, fog, x, y, n - 2, &revealed);
        refresh_screen();

        if (revealed == (n - 2) * (n - 2) - bombs) {
            display_map(n, map, fog, 1); // reveal all
            printf("Congratulations, you won!\n");
            break;
        }
    }

    free_mem((void **)fog, n);
}
