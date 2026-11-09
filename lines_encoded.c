#include "lines_encoded.h"
#include "memory.h"

void initLinesEncoded(LinesEncoded *lines) {
    lines->count = 0;
    lines->capacity = 0;
    lines->lines = NULL;
}
void writeLineToEnconding(LinesEncoded *lines, int line, uint8_t byte) {
    if (lines->count > 0 && lines->lines[lines->count - 1].line == line) {
        lines->lines[lines->count - 1].times += 1;
        return;
    }

    if (lines->capacity < lines->count + 1) {
        int oldCapacity = lines->capacity;
        lines->capacity = GROW_CAPACITY(oldCapacity);
        lines->lines =
            GROW_ARRAY(Line, lines->lines, oldCapacity, lines->capacity);
    }

    Line new_entry;
    new_entry.line = line;
    new_entry.code_first_idx = byte;
    new_entry.times = 1;
    lines->lines[lines->count] = new_entry;
    lines->count++;
}

void freeLinesEncoded(LinesEncoded *lines) {
    FREE_ARRAY(Line, lines->lines, lines->count);
    initLinesEncoded(lines);
}
