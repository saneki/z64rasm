#include "dpad.h"
#include "gfx.h"
#include "hacks.h"
#include "util.h"

void c_init() {
    heap_init();
    gfx_init();
    dpad_init();
}

//void before_game_state_update() {
//}

//void after_game_state_update() {
//}

void before_non_menu_update() {
    do_hacks_per_game_frame();
    handle_dpad();
}
