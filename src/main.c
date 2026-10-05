#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "levenshtein_distance.h"

int main() {
    int a;
    char word_1[50], word_2[50]; 

    assert((minValue(3, 4, 5)) == 3);
    assert((minValue(4, 3, 5)) == 3);
    assert((minValue(5, 4, 3)) == 3);
    assert((minValue(3, 3, 3)) == 3);

    printf("\n1st Word: ");
    fgets(word_1, 50, stdin);

    //Gets the '\n' of the output and puts a null value in place
    word_1[strcspn(word_1, "\n")] = '\0';

    printf("\n2nd Word: ");
    fgets(word_2, 50, stdin);
    
    word_2[strcspn(word_2, "\n")] = '\0';

    calculateDistance(word_1, word_2);
    scanf("%d", &a);

    return 0;
}