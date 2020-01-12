#include <stdbool.h>
#include "dpad.h"
#include "external_effects.h"
#include "gfx.h"
#include "hud_colors.h"
#include "icetrap.h"
#include "quest_items.h"
#include "save_file.h"
#include "util.h"
#include "z2.h"

void c_init() {
    heap_init();
    gfx_init();
    dpad_init();
    hud_colors_init();
}

/**
 * Hook function called after inventory & flags cleared via Song of Time.
 **/
void after_song_of_time_clear(z2_game_t *game) {
    quest_items_after_song_of_time_clear();
}

void before_player_actor_update(z2_link_t *link, z2_game_t *game) {
    dpad_before_player_actor_update(link, game);
    handle_external_effects(link, game);
    save_file_init();
}

bool before_damage_process(z2_link_t *link, z2_game_t *game) {
    return icetrap_give(link, game);
}
