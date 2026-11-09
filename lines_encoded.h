#ifndef clox_lines_encoded_h
#define clox_lines_encoded_h

#include "common.h"
#include <stdint.h>

typedef struct {
    uint8_t code_first_idx;
    int line;
    int times;
} Line; // Run-length encoded

typedef struct {
    int capacity;
    int count;
    Line *lines;
} LinesEncoded;

void initLinesEncoded(LinesEncoded *array);
void writeLineToEnconding(LinesEncoded *array, int line, uint8_t byte);
void freeLinesEncoded(LinesEncoded *array);

#endif
