#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "levenshtein_distance.h"

int main() {
    int table[MAX_CHAR][MAX_CHAR], a;
    char word_1[MAX_CHAR], word_2[MAX_CHAR]; 

    printf("\n1st Word: ");
    fgets(word_1, MAX_CHAR, stdin);

    //Gets the '\n' of the output and puts a null value in place
    word_1[strcspn(word_1, "\n")] = '\0';

    printf("\n2nd Word: ");
    fgets(word_2, MAX_CHAR, stdin);
    
    word_2[strcspn(word_2, "\n")] = '\0';

    //Gets the length of the words;
    int len_word_1 = strlen(word_1),
    len_word_2 = strlen(word_2); 

    createLevenshteinTable(table, len_word_1, len_word_2);

    calculateDistance(table, word_1, word_2, len_word_1, len_word_2, 1, 1);

    printf("Distance: %d", table[len_word_1][len_word_2]);

    scanf("%d", &a);

    return 0;
}