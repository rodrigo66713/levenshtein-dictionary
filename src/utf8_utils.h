#ifndef UTF8_UTILS_H
#define UTF8_UTILS_H

// Configura o console para UTF-8 (só faz algo no Windows).
// Chame como primeira linha da main.
void setupUtf8Console(void);

// Recebe o segundo byte de um par UTF-8 que começa com 0xC3
// e devolve a letra sem acento (minúscula), ou 0 se não for mapeado.
char removeAccent(unsigned char second_byte);

// Converte o texto para minúsculas e sem acento, modificando a própria string.
void normalizeWord(char *text);

#endif 