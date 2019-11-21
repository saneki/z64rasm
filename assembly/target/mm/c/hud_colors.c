#include <stdbool.h>
#include "z64.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} z64_color_rgb8_t;

// Infinite magic meter color (blue).
z64_color_rgb8_t MAGIC_INF_COLOR_CONFIG = { 0x00, 0x00, 0xC8 };

// Magic meter color (green).
z64_color_rgb8_t MAGIC_COLOR_CONFIG = { 0x00, 0xC8, 0x00 };

static uint32_t color_rgb8_to_int(z64_color_rgb8_t color, uint8_t alpha) {
    return (color.r << 24) | (color.g << 16) | (color.b << 8) | alpha;
}

uint32_t get_magic_meter_color(bool inf) {
    uint8_t alpha = z64_game.sub_169E8.rupees_alpha & 0xFF;
    if (inf) {
        return color_rgb8_to_int(MAGIC_INF_COLOR_CONFIG, alpha);
    } else {
        return color_rgb8_to_int(MAGIC_COLOR_CONFIG, alpha);
    }
}
