#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "map.h"
#include "utils.h"
#include "score.h"


#define CONFIG_FILE "minesweeper.cfg"

// Convert code
int difficulty_from_string(const char *arg) {
    if (strcmp(arg, "easy") == 0) {
        return 1;  // Easy
    } else if (strcmp(arg, "medium") == 0) {
        return 2;  // Medium
    } else if (strcmp(arg, "hard") == 0) {
        return 3;  // Hard
    }
    return 0;  // Invalid or quit
}


void log_score_python(const char* player_name, int difficulty, double elapsed_time) {
    Py_Initialize();

    PyObject *pName = PyUnicode_DecodeFSDefault("score_logger"); // your python script name without .py
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "log_score");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pArgs = PyTuple_New(3);
            PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(player_name));
            PyTuple_SetItem(pArgs, 1, PyLong_FromLong(difficulty));
            PyTuple_SetItem(pArgs, 2, PyFloat_FromDouble(elapsed_time));

            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            if (pValue == NULL) {
                PyErr_Print();
                fprintf(stderr, "Failed to call Python function log_score\n");
            }
            Py_XDECREF(pValue);
            Py_DECREF(pArgs);
            Py_DECREF(pFunc);
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"log_score\"\n");
        }
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"score_logger\" module\n");
    }

    Py_Finalize();
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

    int n = board_size + 2;  // +padding

    char **map = generate_map(n);
    if (!map) {
        fprintf(stderr, "Memory allocation failed. Aborting.\n");
        return 1;
    }

    place_bombs(map, n - 2, config);  // - padding

    refresh_screen();

    // Start timer
    clock_t start_time = clock();

    // Gameplay: should return player name or store it somewhere
    char player_name[50] = "Player"; // default name, ideally obtained during gameplay

    gameplay(n, map, config);

    // Stop timer
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Game duration: %.2f seconds\n", elapsed_time);

    // Log  Python
    log_score_python(player_name, difficulty, elapsed_time);

    free_mem((void **)map, n);
    return 0;
}
