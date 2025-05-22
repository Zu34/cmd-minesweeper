#ifndef MAP_H
#define MAP_H

char **generate_map(int n);
int **generate_fog(int n);
void place_bombs(char **map, int n, BombConfig config);
void display_map(int n, char **map, int **fog, int reveal_all);
void fill(char **map, int **fog, int x, int y, int size, int *count);

#endif // MAP_H
