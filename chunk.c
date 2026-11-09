#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "lines_encoded.h"
#include "memory.h"

void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
    initLinesEncoded(&chunk->lines_encoded);
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    freeLinesEncoded(&chunk->lines_encoded);
    initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int old_capacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_capacity);
        chunk->code =
            GROW_ARRAY(uint8_t, chunk->code, old_capacity, chunk->capacity);
        chunk->lines =
            GROW_ARRAY(int, chunk->lines, old_capacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    writeLineToEnconding(&chunk->lines_encoded, line, byte);
    chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

int getLine(Chunk *chunk, int offset) {
    int line_count = 0;
    for (int i = 0; i < chunk->count; i++) {
        for (int j = 0; j < chunk->lines_encoded.lines[i].times; j++) {
            if (line_count == offset) {
                return chunk->lines_encoded.lines[i].line;
            }
            line_count += 1;
        }
    }
    return -1;
}
