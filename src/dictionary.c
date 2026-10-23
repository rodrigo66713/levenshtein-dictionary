#include <stdio.h>
#include <string.h>

#include "levenshtein_distance.h"
#include "dictionary.h"

#define MAX_MEANING 256
#define MAX_ENTRIES 1000
#define DELIMITER   ';'

// Retorna a quantidade de entradas lidas, ou -1 se não conseguir abrir o arquivo.
int loadDictionary(const char *path, Entry entries[], int max_entries) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror(path);
        return -1;
    }

    char line[MAX_CHAR + MAX_MEANING + 2];
    int count = 0;

    while (count < max_entries && fgets(line, sizeof(line), file) != NULL) {
        // Linha maior que o buffer: descarta o resto dela
        if (strchr(line, '\n') == NULL && !feof(file)) {
            int c;
            while ((c = fgetc(file)) != '\n' && c != EOF);
        }

        // Remove '\n' e '\r' (arquivos criados no Windows)
        line[strcspn(line, "\r\n")] = '\0';

        // Separa palavra e significado
        char *separator = strchr(line, DELIMITER);
        if (separator == NULL) {
            continue; // linha vazia ou sem delimitador
        }
        *separator = '\0';

        char *word = line;
        char *meaning = separator + 1;

        // Ignora palavra vazia ou grande demais para a tabela de distância
        if (word[0] == '\0' || strlen(word) >= MAX_CHAR) {
            continue;
        }

        snprintf(entries[count].word, sizeof(entries[count].word), "%s", word);
        snprintf(entries[count].meaning, sizeof(entries[count].meaning), "%s", meaning);
        count++;
    }

    fclose(file);
    return count;
}

void calculateAllDistances(
    int table[MAX_CHAR][MAX_CHAR],
    char input[MAX_CHAR],
    Entry entries[],
    int total
) {
    int len_input = strlen(input);

    for (int k = 0; k < total; k++) {
        int len_word = strlen(entries[k].word);

        // Os tamanhos mudam a cada palavra, então a tabela é refeita
        createLevenshteinTable(table, len_input, len_word);

        // Se uma das palavras é vazia, a resposta já está nos casos base
        if (len_input > 0 && len_word > 0) {
            calculateDistance(table, input, entries[k].word,
                              len_input, len_word, 1, 1);
        }

        // Linha = tamanho da palavra do dicionário, coluna = tamanho da entrada
        entries[k].distance = table[len_word][len_input];
    }
}

void selectClosest(
    Entry entries[],
    int total, 
    int how_many
) {
    // Se o dicionário tiver menos palavras que o pedido, limita
    int limit = (how_many < total) ? how_many : total;

    for (int i = 0; i < limit; i++) {
        int smallest = i;

        for (int j = i + 1; j < total; j++) {
            if (entries[j].distance < entries[smallest].distance) {
                smallest = j;
            }
        }

        if (smallest != i) {
            Entry temp = entries[i];
            entries[i] = entries[smallest];
            entries[smallest] = temp;
        }
    }
}

void printClosest(
    const Entry entries[], 
    int total, 
    int how_many
) {
    int limit = (how_many < total) ? how_many : total;

    for (int i = 0; i < limit; i++) {
        printf("\n===============================================================\n");
        printf("%d. %s (Distancia: %d)\n", i + 1, entries[i].word, entries[i].distance);
        printf("\n%s", entries[i].meaning);
        printf("\n===============================================================\n");
    }
}
