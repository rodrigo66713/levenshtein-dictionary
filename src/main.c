#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "levenshtein_distance.h"
#include "dictionary.h"

static Entry dictionary[MAX_ENTRIES];

int main() {
    int total = loadDictionary("data/dictionary.txt", dictionary, MAX_ENTRIES);

    printf("%d palavras carregadas.\n", total);

    int table[MAX_CHAR][MAX_CHAR];
    int distances[MAX_ENTRIES];
    char input[MAX_CHAR];

    printf("Palavra: ");
    fgets(input, MAX_CHAR, stdin);
    input[strcspn(input, "\r\n")] = '\0';

    calculateAllDistances(table, input, dictionary, total, distances);
    printDistances(dictionary, distances, total);

    return 0;
}