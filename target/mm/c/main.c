#include <stdbool.h>
#include "dpad.h"
#include "external_effects.h"
#include "gfx.h"
#include "hud_colors.h"
#include "icetrap.h"
#include "util.h"

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

void before_non_menu_update() {
    do_dpad_per_game_frame();
    handle_external_effects();
}

bool before_damage_process() {
    return give_icetrap();
}

void before_main_menu_draw() {
    hud_colors_main_menu_init();
}
