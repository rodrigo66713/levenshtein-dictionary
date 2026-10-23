#ifndef DICTIONARY_H
#define DICTIONARY_H

#define MAX_MEANING 256
#define MAX_ENTRIES 1000
#define DELIMITER   ';'

typedef struct {
    char word[MAX_CHAR];
    char meaning[MAX_MEANING];
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
    int total,
    int distances[]
);

void printDistances(
    Entry entries[],
    int distances[],
    int total
);
#endif