#ifndef LEVENSHTEIN_DISTANCE_H
#define LEVENSHTEIN_DISTANCE_H

#define MAX_CHAR 50

void calculateDistance(
    int table[MAX_CHAR][MAX_CHAR],
    char word_1[MAX_CHAR], 
    char word_2[MAX_CHAR], 
    int len_word_1, 
    int len_word_2,
    int i,
    int j
);

void createLevenshteinTable(
    int table[MAX_CHAR][MAX_CHAR], 
    int len_word_1, 
    int len_word_2
);

int minValue(
    int remove, 
    int insert, 
    int substitution
);

#endif 