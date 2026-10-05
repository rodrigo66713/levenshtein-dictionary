#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levenshtein_distance.h"

/*
    1- Create Levenshtein's Table - STATUS: OK 
    
    In a Loop:    
        2- Calculate Remove, Insert and Substitution Values
        3- Calculate the minimun value between the three of them - STATUS: ONGOING
        4- Insert on the table
    
    5- Output the Final Distance
*/

void calculateDistance(char word_1[MAX_CHAR], char word_2[MAX_CHAR]) {
    int word_1_length = strlen(word_1),
    word_2_length = strlen(word_2); 
    
    int table[MAX_CHAR][MAX_CHAR];

    createLevenshteinTable(table, word_1_length, word_2_length);

    
}

void createLevenshteinTable(int table[MAX_CHAR][MAX_CHAR], int word_1_length, int word_2_length) {
    for (int i = 0; i <= word_2_length; i++) {
        for (int j = 0; j <= word_1_length; j++) {
            if (i == 0) {
                table[i][j] = j;
            } else if (j == 0) {
                table[i][j] = i;
            } else {
                table[i][j] = '\0';
            }

            printf("   %d", table[i][j]);
        }
        printf("\n");
    }
}

int minValue(
    int remove, 
    int insert, 
    int substitution
) {
    if (remove == substitution & remove == insert && substitution == insert){
        return remove;
    }
    else if (remove < insert && remove < substitution) {
        return remove;    
    } 
    else if (insert < remove && insert < substitution){
        return insert;
    } 
    else if (substitution < remove && substitution < insert) {
        return substitution;
    }
}