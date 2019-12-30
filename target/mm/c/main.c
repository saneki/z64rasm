#include <stdbool.h>
#include "dpad.h"
#include "external_effects.h"
#include "gfx.h"
#include "hud_colors.h"
#include "icetrap.h"
#include "util.h"
#include "z2.h"

void c_init() {
    heap_init();
    gfx_init();
    dpad_init();
    hud_colors_init();
}

//void before_game_state_update() {
//}

//void after_game_state_update() {
//}

void before_non_menu_update(z2_link_t *link, z2_game_t *game) {
    dpad_do_per_game_frame(link, game);
    handle_external_effects(link, game);
}

bool before_damage_process(z2_link_t *link, z2_game_t *game) {
    return give_icetrap(link, game);
}
