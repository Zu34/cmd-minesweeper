#ifndef GAME_H
#define GAME_H

#define NEWLINE "\n"
// #define NEWLINE "\r\n"
    #define CHARNEWLINE '\r'
typedef struct {
    int easy, medium, hard;
} BombConfig;

// Game flow
int main_menu(void);
void gameplay(int n, char **map, BombConfig config);
int load_config(const char *filename, int *board_size, BombConfig *config);

// Map utilities
char **generate_map(int n);
int **generate_fog(int n);
void place_bombs(char **map, int n, BombConfig config);
void display_map(int n, char **map, int **fog, int reveal_all);
void fill(char **map, int **fog, int x, int y, int n, int *count);
void free_mem(void **matrix, int n);

// Utility functions
void refresh_screen(void);
void clear_buffer(void);

#endif
