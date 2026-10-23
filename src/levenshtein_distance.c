#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levenshtein_distance.h"

/*
    1- Criar Tabela Inicial de Levenshtein - STATUS: OK 
    
    Em loop: - STATUS: OK 
        2- Calcular os valores de Remoção, Inserção e Substituição - STATUS: OK
        3- Calcular o valor mínimo entre os três - STATUS: OK
        4- Inserir na tabela - STATUS: OK
    
    5- Exibir a Distância Final - STATUS: OK
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

    if (word_1[j-1] != word_2[i-1]) {
        cost = 1;
    }

    remove = table[i-1][j] + 1;
    insert = table[i][j-1] + 1;
    substitution = table[i-1][j-1] + cost;

    table[i][j] = minValue(remove, insert, substitution);

    if(j < len_word_1){
        calculateDistance(table, word_1, word_2, len_word_1, len_word_2, i, j+1);
    } else if (i < len_word_2){
        calculateDistance(table, word_1, word_2, len_word_1, len_word_2, i+1, 1);
    } else if (i == len_word_2 && j == len_word_1){
        return;
    }
}

void createLevenshteinTable(
    int table[MAX_CHAR][MAX_CHAR], 
    int len_word_1, 
    int len_word_2
) {
    for (int i = 0; i <= len_word_1; i++) {
        for (int j = 0; j <= len_word_2; j++) {
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
    if ((remove == substitution) && (remove == insert) && (substitution == insert)){
        return remove;
    }
    else if ((remove < insert) && (remove < substitution)) {
        return remove;    
    } 
    else if ((insert < remove) && (insert < substitution)){
        return insert;
    } 
    else if ((substitution < remove) && (substitution < insert)) {
        return substitution;
    }
}