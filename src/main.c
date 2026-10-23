#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levenshtein_distance.h"
#include "dictionary.h"
#include "utf8_utils.h" 

#define SUGGESTIONS 5

static Entry dictionary[MAX_ENTRIES];

int main() {
    setupUtf8Console();
    
    int total = loadDictionary("data/dictionary.txt", dictionary, MAX_ENTRIES);
    int table[MAX_CHAR][MAX_CHAR];
    char input[MAX_CHAR];
    
    printf("\033[2J\033[H");
    printf("===============================================================\n");
    printf("               O DICIONARIO DE LEVENSHTEIN                     \n");
    printf("===============================================================\n");

    printf("\n%d palavras carregadas.\n", total);

    while (1) {
        printf("\nInsira uma palavra: ");
        fgets(input, MAX_CHAR, stdin);
        input[strcspn(input, "\r\n")] = '\0';

        normalizeWord(input);
        calculateAllDistances(table, input, dictionary, total);
        selectClosest(dictionary, total, SUGGESTIONS);
        printClosest(dictionary, total, SUGGESTIONS);
        
        printf("\nAperte ENTER para continuar...");
        getchar();

        // Clear the terminal
        printf("\033[2J\033[H");
    }

    return 0;
}