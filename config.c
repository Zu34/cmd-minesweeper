#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

int load_config(const char *filename, int *board_size, BombConfig *config) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open config file '%s'. Using defaults.\n", filename);
        return -1;
    }

    char line[128];
    while (fgets(line, sizeof(line), file)) {
     
        if (line[0] == '#' || line[0] == '\n')
            continue;

        
        line[strcspn(line, "\r\n")] = 0;

        char key[64];
        int value;
        if (sscanf(line, "%63[^=]=%d", key, &value) == 2) {
            if (strcmp(key, "board_size") == 0) {
                *board_size = value;
            } else if (strcmp(key, "bomb_easy") == 0) {
                config->easy = value;
            } else if (strcmp(key, "bomb_medium") == 0) {
                config->medium = value;
            } else if (strcmp(key, "bomb_hard") == 0) {
                config->hard = value;
            }
            // else ignore unknown keys
        }
    }

    fclose(file);
    return 0;
}
