#include "quest_items.h"
#include "z2.h"

/**
 * Hook function called after some savedata has been loaded into z2_file.
 **/
void savedata_after_load(z2_game_t *game, z2_camera_t *camera) {
    // Todo
}

/**
 * Hook function called after savedata prepared (inventory & flags cleared via Song of Time).
 **/
void savedata_after_prepare(z2_game_t *game) {
    quest_items_after_song_of_time_clear();
}
