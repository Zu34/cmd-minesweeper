
// main.c
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "map.h"
#include "utils.h"

int main(void)
{
    BombConfig bomb_config = {
        .easy = 10,     // Max ~63
        .medium = 50,   // Max ~255
        .hard = 100     // Max ~575
    };

    int difficulty = main_menu();  // Returns 1 (Easy), 2 (Medium), 3 (Hard), or 0 (Quit)
    if (difficulty == 0) {
        printf("Goodbye!\n");
        return 0;
    }

    int n = difficulty * 8 + 2; // e.g., 10x10, 18x18, 26x26 + 2 for border padding

    char **map = generate_map(n);
    if (!map) {
        fprintf(stderr, "Failed to allocate memory for map.\n");
        return 1;
    }

    place_bombs(map, n - 2, bomb_config); // -2 to account for internal playable area

    refresh_screen();
    gameplay(n, map, bomb_config);

    free_mem((void **)map, n);
    return 0;
}
