#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levenshtein_distance.h"

/*
    1- Create Levenshtein's Table - STATUS: OK 
    
    In a Loop - STATUS: ONGOING 
        2- Calculate Remove, Insert and Substitution Values
        3- Calculate the minimun value between the three of them - STATUS: OK
        4- Insert on the table
    
    5- Output the Final Distance
*/

void calculateDistance(
    int table[MAX_CHAR][MAX_CHAR], 
    char word_1[MAX_CHAR], 
    char word_2[MAX_CHAR], 
    int len_word_1, 
    int len_word_2,
    int i, 
    int j
) {
    int remove, insert, substitution, cost = 0;
    
    //recursive condition
    if (i == len_word_2 && j == len_word_1){
        return;
    }

    if (word_1[j] == word_2[i]) {
        cost = 1;
    }

    remove = table[i-1][j] + 1;
    insert = table[i][j-1] + 1;
    substitution = table[i-1][j-1] + cost;

    table[i][j] = minValue(remove, insert, substitution);
    
    if(j <= len_word_1){
        calculateDistance(table, word_1, word_2, len_word_1, len_word_2, i, j+1);
    } else if (i <= len_word_2){
        calculateDistance(table, word_1, word_2, len_word_1, len_word_2, i+1, 1);
    }
}

void createLevenshteinTable(
    int table[MAX_CHAR][MAX_CHAR], 
    int len_word_1, 
    int len_word_2
) {
    for (int i = 0; i <= len_word_2; i++) {
        for (int j = 0; j <= len_word_1; j++) {
            if (i == 0) {
                table[i][j] = j;
            } else if (j == 0) {
                table[i][j] = i;
            } else {
                table[i][j] = '\0';
            }
        }
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