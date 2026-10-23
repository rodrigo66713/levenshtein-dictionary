#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utf8_utils.h"

#ifdef _WIN32
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

static UINT original_input_cp;
static UINT original_output_cp;

static void restoreConsole(void) {
    SetConsoleCP(original_input_cp);
    SetConsoleOutputCP(original_output_cp);
}
#endif

void setupUtf8Console(void) {
#ifdef _WIN32
    original_input_cp = GetConsoleCP();
    original_output_cp = GetConsoleOutputCP();

    SetConsoleCP(CP_UTF8);        // entrada 
    SetConsoleOutputCP(CP_UTF8);  // saída 
    atexit(restoreConsole);       // devolve o console ao estado original

    // Habilita sequências ANSI (usadas para limpar a tela)
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (out != INVALID_HANDLE_VALUE && GetConsoleMode(out, &mode)) {
        SetConsoleMode(out, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
#endif
}

//Remove os acentos e caracteres especiais
char removeAccent(unsigned char second_byte) {
    switch (second_byte) {
        // à á â ã ä  |  À Á Â Ã Ä
        case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4:
        case 0x80: case 0x81: case 0x82: case 0x83: case 0x84:
            return 'a';

        // ç  |  Ç
        case 0xA7: case 0x87:
            return 'c';

        // è é ê ë  |  È É Ê Ë
        case 0xA8: case 0xA9: case 0xAA: case 0xAB:
        case 0x88: case 0x89: case 0x8A: case 0x8B:
            return 'e';

        // ì í î ï  |  Ì Í Î Ï
        case 0xAC: case 0xAD: case 0xAE: case 0xAF:
        case 0x8C: case 0x8D: case 0x8E: case 0x8F:
            return 'i';

        // ñ  |  Ñ
        case 0xB1: case 0x91:
            return 'n';

        // ò ó ô õ ö  |  Ò Ó Ô Õ Ö
        case 0xB2: case 0xB3: case 0xB4: case 0xB5: case 0xB6:
        case 0x92: case 0x93: case 0x94: case 0x95: case 0x96:
            return 'o';

        // ù ú û ü  |  Ù Ú Û Ü
        case 0xB9: case 0xBA: case 0xBB: case 0xBC:
        case 0x99: case 0x9A: case 0x9B: case 0x9C:
            return 'u';

        default:
            return 0;
    }
}

// Normaliza a entrada do usuário, deixando-as minúsculas e sem acentos.
void normalizeWord(char *text) {
    int read = 0;
    int write = 0;

    while (text[read] != '\0') {
        unsigned char current = (unsigned char) text[read];

        if (current == 0xC3 && text[read + 1] != '\0') {
            char plain = removeAccent((unsigned char) text[read + 1]);

            if (plain != 0) {
                text[write++] = plain;
                read += 2;
            } else {
                // Par não mapeado: copia os dois bytes sem alterar
                text[write++] = text[read++];
                text[write++] = text[read++];
            }
        } else {
            text[write++] = (char) tolower(current);
            read++;
        }
    }

    text[write] = '\0';
}