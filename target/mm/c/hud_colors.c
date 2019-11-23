#include <stdbool.h>
#include "color.h"
#include "z64.h"

// Infinite magic meter color (blue).
z64_color_rgb8_t MAGIC_INF_COLOR_CONFIG = { 0x00, 0x00, 0xC8 };

// Magic meter color (green).
z64_color_rgb8_t MAGIC_COLOR_CONFIG = { 0x00, 0xC8, 0x00 };

// Map color.
z64_color_rgba8_t MAP_COLOR_CONFIG = { 0x00, 0xFF, 0xFF, 0xA0 };

// Map player cursor color.
z64_color_rgb8_t MAP_PLAYER_CURSOR_COLOR_CONFIG = { 0xC8, 0xFF, 0x00 };

// Map entrance cursor color.
z64_color_rgb8_t MAP_ENTRANCE_CURSOR_COLOR_CONFIG = { 0xC8, 0x00, 0x00 };

// Clock diamond color.
z64_color_rgb8_t CLOCK_DIAMOND_COLOR_CONFIG = { 0x00, 0xAA, 0x64 };

// Inverted clock diamond color (1).
z64_color_rgb8_t CLOCK_INVERTED_DIAMOND_COLOR1_CONFIG = { 0x64, 0xCD, 0xFF };

// Inverted clock diamond color (2).
z64_color_rgb8_t CLOCK_INVERTED_DIAMOND_COLOR2_CONFIG = { 0x00, 0x9B, 0xFF };

// A button color.
z64_color_rgb8_t A_BUTTON_COLOR_CONFIG = { 0x64, 0xC8, 0xFF };

// B button color.
z64_color_rgb8_t B_BUTTON_COLOR_CONFIG = { 0x64, 0xFF, 0x78 };

// C buttons color.
z64_color_rgb8_t C_BUTTON_COLOR_CONFIG = { 0xFF, 0xF0, 0x00 };

// Start button color.
z64_color_rgb8_t START_BUTTON_COLOR_CONFIG = { 0xFF, 0x82, 0x3C };

// Heart color.
z64_color_rgb8_t HEART_COLOR_CONFIG = { 0xFF, 0x46, 0x32 };

// Heart (double defense) color.
z64_color_rgb8_t HEART_DD_COLOR_CONFIG = { 0xC8, 0x00, 0x00 };

static uint32_t color_rgb8_to_int(z64_color_rgb8_t color, uint8_t alpha) {
    return (color.r << 24) | (color.g << 16) | (color.b << 8) | alpha;
}

static uint32_t color_rgba8_to_int(z64_color_rgba8_t color) {
    return (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}

uint32_t get_magic_meter_color(bool inf) {
    uint8_t alpha = z64_game.sub_169E8.rupees_alpha & 0xFF;
    if (inf) {
        return color_rgb8_to_int(MAGIC_INF_COLOR_CONFIG, alpha);
    } else {
        return color_rgb8_to_int(MAGIC_COLOR_CONFIG, alpha);
    }
}

uint32_t get_map_color() {
    return color_rgba8_to_int(MAP_COLOR_CONFIG);
}

uint32_t get_map_player_cursor_color() {
    uint8_t alpha = z64_game.sub_169E8.minimap_alpha & 0xFF;
    return color_rgb8_to_int(MAP_PLAYER_CURSOR_COLOR_CONFIG, alpha);
}

uint32_t get_map_entrance_cursor_color() {
    uint8_t alpha = z64_game.sub_169E8.minimap_alpha & 0xFF;
    return color_rgb8_to_int(MAP_ENTRANCE_CURSOR_COLOR_CONFIG, alpha);
}

uint32_t get_clock_diamond_color() {
    uint8_t alpha = (uint8_t)(*(uint16_t *)(0x801BFB2C));
    return color_rgb8_to_int(CLOCK_DIAMOND_COLOR_CONFIG, alpha);
}

uint16_t get_inverted_clock_diamond_color(uint8_t idx) {
    z64_color_rgb8_t colors;
    int16_t mode = *(int16_t *)0x801BFBE8;

    if (idx > 2) {
        return 0;
    }

    // Mode should be either 0 (first color) or 1 (second color)
    if (!mode) {
        colors = CLOCK_INVERTED_DIAMOND_COLOR1_CONFIG;
    } else {
        colors = CLOCK_INVERTED_DIAMOND_COLOR2_CONFIG;
    }

    return colors.bytes[idx];
}

uint32_t get_a_button_color() {
    uint8_t alpha = z64_game.sub_169E8.a_button_alpha & 0xFF;
    return color_rgb8_to_int(A_BUTTON_COLOR_CONFIG, alpha);
}

uint32_t get_b_button_color() {
    // Alpha won't be used but set it anyway
    uint8_t alpha = z64_game.sub_169E8.b_button_alpha & 0xFF;
    return color_rgb8_to_int(B_BUTTON_COLOR_CONFIG, alpha);
}

uint32_t get_c_button_color(uint16_t alpha) {
    return color_rgb8_to_int(C_BUTTON_COLOR_CONFIG, alpha & 0xFF);
}

uint32_t get_start_button_color(uint16_t alpha) {
    return color_rgb8_to_int(START_BUTTON_COLOR_CONFIG, alpha & 0xFF);
}

void update_heart_colors(z64_game_t *game) {
    // Normal heart colors
    z64_color_rgb16_2_t *heart = &(z64_game.sub_169E8.heart_inner_rgb);
    z64_color_rgb16_t *heart_beating = &(z64_game.sub_169E8.heartbeat_inner_rgb);

    // Double defense heart colors
    z64_color_rgb16_t *heart_dd = &(z64_file.heart_dd_rgb);
    z64_color_rgb16_t *heart_dd_beating = &(z64_file.heart_dd_beating_rgb);

    // This function writes constant values to where the heart colors are stored.
    // It might also do other things.
    z64_WriteHeartColors(game);

    // Update heart colors (normal)
    heart->r1 = HEART_COLOR_CONFIG.r;
    heart->g1 = HEART_COLOR_CONFIG.g;
    heart->b1 = HEART_COLOR_CONFIG.b;
    heart_beating->r = HEART_COLOR_CONFIG.r;
    heart_beating->g = HEART_COLOR_CONFIG.g;
    heart_beating->b = HEART_COLOR_CONFIG.b;

    // Update heart colors (double defense)
    heart_dd->r = HEART_DD_COLOR_CONFIG.r;
    heart_dd->g = HEART_DD_COLOR_CONFIG.g;
    heart_dd->b = HEART_DD_COLOR_CONFIG.b;
    heart_dd_beating->r = HEART_DD_COLOR_CONFIG.r;
    heart_dd_beating->g = HEART_DD_COLOR_CONFIG.g;
    heart_dd_beating->b = HEART_DD_COLOR_CONFIG.b;
}
