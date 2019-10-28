#include "dpad.h"
#include "gfx.h"
#include "util.h"

void c_init() {
    heap_init();
    gfx_init();
    dpad_init();
}

void before_game_state_update() {
}

void after_game_state_update() {
}

void before_non_menu_update() {
    handle_dpad();
}
