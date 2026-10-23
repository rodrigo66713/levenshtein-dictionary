#ifndef DICTIONARY_H
#define DICTIONARY_H

#define MAX_MEANING 256
#define MAX_ENTRIES 1000
#define DELIMITER   ';'

typedef struct {
    char word[MAX_CHAR];
    char meaning[MAX_MEANING];
    int distance;
} Entry;

int loadDictionary(
    const char *path, 
    Entry entries[], 
    int max_entries
);

void calculateAllDistances(
    int table[MAX_CHAR][MAX_CHAR],
    char input[MAX_CHAR],
    Entry entries[],
    int total
);

void selectClosest(
    Entry entries[],
    int total, 
    int how_many
);

void printClosest(
    const Entry entries[], 
    int total, 
    int how_many
);

#endif