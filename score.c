// score.c
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"

int load_scores(ScoreEntry scores[], int max_scores) {
    FILE *file = fopen("scores.txt", "r");
    if (!file) return 0;

    int count = 0;
    while (count < max_scores && fscanf(file, "%63[^|]| %49[^|]| %15[^|]| %lf sec\n",
           scores[count].datetime, scores[count].name,
           scores[count].difficulty, &scores[count].time_sec) == 4) {
        count++;
    }

    fclose(file);
    return count;
}

int compare_scores(const void *a, const void *b) {
    double t1 = ((ScoreEntry *)a)->time_sec;
    double t2 = ((ScoreEntry *)b)->time_sec;
    return (t1 > t2) - (t1 < t2);
}

void display_top_scores() {
    ScoreEntry scores[MAX_SCORES];
    int total = load_scores(scores, MAX_SCORES);

    if (total == 0) {
        printf("No scores available.\n");
        return;
    }

    qsort(scores, total, sizeof(ScoreEntry), compare_scores);
    printf("\n🏆 Top Scores:\n");
    for (int i = 0; i < total && i < 5; i++) {
        printf("%d. %s - %s - %s - %.2f sec\n", i + 1,
               scores[i].datetime, scores[i].name,
               scores[i].difficulty, scores[i].time_sec);
    }
}

void log_score_python(const char *name, const char *difficulty, double time_sec) {
    Py_Initialize();

    PyObject *pName = PyUnicode_DecodeFSDefault("log_score");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "log_score");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pArgs = PyTuple_New(3);
            PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(name));
            PyTuple_SetItem(pArgs, 1, PyUnicode_FromString(difficulty));
            PyTuple_SetItem(pArgs, 2, PyFloat_FromDouble(time_sec));

            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            if (!pValue) PyErr_Print();

            Py_XDECREF(pValue);
            Py_DECREF(pArgs);
            Py_DECREF(pFunc);
        } else {
            PyErr_Print();
            fprintf(stderr, "Python function 'log_score' not callable.\n");
        }
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
        fprintf(stderr, "Failed to load Python module 'log_score'\n");
    }

    Py_Finalize();
}

