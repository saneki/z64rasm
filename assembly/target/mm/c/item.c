#include <stdbool.h>
#include "z64.h"

void check_item_usability(bool *dest, uint8_t b, uint8_t c1, uint8_t c2, uint8_t c3) {
    uint8_t previous[4], prevstates[5];

    // Backup modified fields
    uint8_t game_state = z64_file.game_state;
    uint8_t pre_game_state = z64_file.pre_game_state;
    uint8_t alpha_transition = z64_file.alpha_transition;
    uint8_t sub_game_state = z64_file.sub_game_state;

    // Backup button items
    previous[0] = z64_file.b_button;
    for (int i = 0; i < 3; i++)
        previous[i+1] = z64_file.c_buttons[i];

    // Backup button states
    prevstates[0] = z64_file.a_button_usable;
    prevstates[1] = z64_file.b_button_usable;
    for (int i = 0; i < 3; i++)
        prevstates[i+2] = z64_file.c_buttons_usable[i];

    z64_file.b_button = b;
    z64_file.c_buttons[0] = c1;
    z64_file.c_buttons[1] = c2;
    z64_file.c_buttons[2] = c3;

    z64_UpdateButtonUsability(&z64_ctxt);

    // Set dest to enabled-states (which are either 0x00 or 0xFF)
    dest[0] = (z64_file.b_button_usable == 0);
    for (int i = 0; i < 3; i++)
        dest[i+1] = (z64_file.c_buttons_usable[i] == 0);

    // Restore button items
    z64_file.b_button = previous[0];
    for (int i = 0; i < 3; i++)
        z64_file.c_buttons[i] = previous[i+1];

    // Restore button states
    z64_file.a_button_usable = prevstates[0];
    z64_file.b_button_usable = prevstates[1];
    for (int i = 0; i < 3; i++)
        z64_file.c_buttons_usable[i] = prevstates[i+2];

    // Restore modified fields
    z64_file.game_state = game_state;
    z64_file.pre_game_state = pre_game_state;
    z64_file.alpha_transition = alpha_transition;
    z64_file.sub_game_state = sub_game_state;
}

bool check_c_item_usable(uint8_t c) {
    bool dest[4];

    check_item_usability(dest, 0xFF, c, 0xFF, 0xFF);
    return dest[1];
}
