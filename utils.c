#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#ifdef _WIN32
    #define CHARNEWLINE '\r'
#else
    #define CHARNEWLINE '\n'
#endif

void refresh_screen(void)
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void clear_buffer(void)
{
    int c;
    while ((c = getchar()) != CHARNEWLINE && c != EOF);
}

void free_mem(void **matrix, int n)
{
    if (!matrix) return;

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
