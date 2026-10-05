#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char word_1[50], word_2[50]; 

    printf("\n1st Word: ");
    fgets(word_1, 50, stdin);

    //Gets the '\n' of the output and puts a null value in place
    word_1[strcspn(word_1, "\n")] = '\0';

    printf("\n2nd Word: ");
    fgets(word_2, 50, stdin);
    
    word_2[strcspn(word_2, "\n")] = '\0';

    printf("\nWord 1: %s \nWord 2: %s", word_1, word_2);

    return 0;
}