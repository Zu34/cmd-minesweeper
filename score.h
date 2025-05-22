// score.h
#ifndef SCORE_H
#define SCORE_H

#define MAX_SCORES 100

typedef struct {
    char datetime[64];
    char name[50];
    char difficulty[16];
    double time_sec;
} ScoreEntry;

int load_scores(ScoreEntry scores[], int max_scores);
int compare_scores(const void *a, const void *b);
void display_top_scores();

#endif
