#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

typedef struct {
    union {
        uint8_t bytes[3];
        struct {
            uint8_t r;
            uint8_t g;
            uint8_t b;
        };
    };
} z64_color_rgb8_t;

typedef struct {
    union {
        uint8_t bytes[4];
        struct {
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;
        };
    };
} z64_color_rgba8_t;

typedef struct {
    union {
        uint16_t words[3];
        struct {
            uint16_t r;
            uint16_t g;
            uint16_t b;
        };
    };
} z64_color_rgb16_t;

typedef struct {
    union {
        uint16_t words[6];
        struct {
            uint16_t r1;
            uint16_t r2;
            uint16_t g1;
            uint16_t g2;
            uint16_t b1;
            uint16_t b2;
        };
    };
} z64_color_rgb16_2_t;

#endif // COLOR_H
