#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define array_size(a) (sizeof(a) / sizeof(a[0]))

void heap_init();
void *heap_alloc(int bytes);

typedef struct {
    uint8_t *buf;
    uint32_t vrom_start;
    uint32_t size;
} file_t;

void file_init(file_t *file);

#endif
