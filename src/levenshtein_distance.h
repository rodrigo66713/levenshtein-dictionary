#ifndef LEVENSHTEIN_DISTANCE_H
#define LEVENSHTEIN_DISTANCE_H

#define MAX_CHAR 50

void calculateDistance(
    char word_1[MAX_CHAR], 
    char word_2[MAX_CHAR]
);

void createLevenshteinTable(
    int table[MAX_CHAR][MAX_CHAR], 
    int word_1_length, 
    int word_2_lenght
);

int minValue(
    int remove, 
    int insert, 
    int substitution
);

#endif 