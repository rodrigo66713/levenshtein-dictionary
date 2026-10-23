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