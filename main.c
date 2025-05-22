#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "map.h"
#include "utils.h"

#define CONFIG_FILE "minesweeper.cfg"

int difficulty_from_string(const char *arg) {
    if (strcmp(arg, "easy") == 0) {
        return 1;  // Easy
    } else if (strcmp(arg, "medium") == 0) {
        return 2;  // Medium
    } else if (strcmp(arg, "hard") == 0) {
        return 3;  // Hard
    }
    return 0;  
}

int main(int argc, char *argv[]) {
    int board_size = 10;  
    BombConfig config = {10, 50, 100};  // default bombs

    
    load_config(CONFIG_FILE, &board_size, &config);

    int difficulty = 0;

    if (argc > 1) {
        difficulty = difficulty_from_string(argv[1]);
        if (difficulty == 0) {
            printf("Invalid difficulty argument.\n");
            return 1;
        }
    } else {
        difficulty = main_menu(); 
        if (difficulty == 0) {
            printf("Goodbye!\n");
            return 0;
        }
    }

    // Adjust board size 
    int n = board_size + 2;  // +padding

    char **map = generate_map(n);
    if (!map) {
        fprintf(stderr, "Memory allocation failed. Aborting.\n");
        return 1;
    }

    place_bombs(map, n - 2, config);  // - padding

    refresh_screen();
    gameplay(n, map, config);

    free_mem((void **)map, n);
    return 0;
}
