#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "map.h"

char **generate_map(int n)
{
    char **map = malloc(n * sizeof(char *));
    if (!map) return NULL;

    for (int i = 0; i < n; i++) {
        map[i] = malloc(n * sizeof(char));
        if (!map[i]) return NULL;
        for (int j = 0; j < n; j++) {
            map[i][j] = '0';
        }
    }
    return map;
}

int **generate_fog(int n)
{
    int **fog = malloc(n * sizeof(int *));
    if (!fog) return NULL;

    for (int i = 0; i < n; i++) {
        fog[i] = malloc(n * sizeof(int));
        if (!fog[i]) return NULL;
        for (int j = 0; j < n; j++) {
            fog[i][j] = 0;
        }
    }
    return fog;
}

void place_bombs(char **map, int n, BombConfig config)
{
    int total = (n == 8) ? config.easy :
                (n == 16) ? config.medium :
                            config.hard;

    srand(time(NULL));
    while (total > 0) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;

        if (map[x][y] != 'b') {
            map[x][y] = 'b';
            total--;

            // Increment surrounding numbers
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (map[nx][ny] != 'b' && map[nx][ny] != '@') {
                        map[nx][ny]++;
                    }
                }
            }
        }
    }

    // Add borders (padding) with '@'
    for (int i = 0; i < n + 2; i++) {
        map[i][0] = map[i][n + 1] = '@';
        map[0][i] = map[n + 1][i] = '@';
    }
}

void display_map(int n, char **map, int **fog, int reveal_all)
{
    printf("   ");
    for (int i = 1; i < n - 1; i++) {
        printf("%2d ", i);
    }
    printf(NEWLINE);

    for (int i = 1; i < n - 1; i++) {
        printf("%2d ", i);
        for (int j = 1; j < n - 1; j++) {
            if (reveal_all || fog[i][j]) {
                char cell = map[i][j];
                printf("%c  ", cell == '0' ? '.' : cell);
            } else {
                printf("=  ");
            }
        }
        printf(NEWLINE);
    }
}

void fill(char **map, int **fog, int x, int y, int size, int *count)
{
    if (fog[x][y]) return;

    fog[x][y] = 1;
    (*count)++;

    if (map[x][y] == '0') {
        // Recursively open neighbors
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 1 && ny >= 1 && nx <= size && ny <= size) {
                fill(map, fog, nx, ny, size, count);
            }
        }
    }
}
