#include <stdbool.h>
#include "z2.h"

void check_item_usability(bool *dest, u8 b, u8 c1, u8 c2, u8 c3) {
    u8 previous[4], prevstates[5];

    // Backup modified fields
    u8 game_state = z2_file.game_state;
    u8 pre_game_state = z2_file.pre_game_state;
    u8 alpha_transition = z2_file.alpha_transition;
    u8 sub_game_state = z2_file.sub_game_state;

    // Backup button items
    for (int i = 0; i < 4; i++)
        previous[i] = z2_file.form_button_item[0].button_item[i];

    // Backup button states
    for (int i = 0; i < 5; i++)
        prevstates[i] = z2_file.buttons_usable[i];

    z2_file.form_button_item[0].b      = b;
    z2_file.form_button_item[0].cleft  = c1;
    z2_file.form_button_item[0].cdown  = c2;
    z2_file.form_button_item[0].cright = c3;

    z2_UpdateButtonUsability(&z2_ctxt);

    // Set dest to enabled-states (which are either 0x00 or 0xFF)
    for (int i = 0; i < 4; i++)
        dest[i] = (z2_file.buttons_usable[i] == 0);

    // Restore button items
    for (int i = 0; i < 4; i++)
        z2_file.form_button_item[0].button_item[i] = previous[i];

    // Restore button states
    for (int i = 0; i < 5; i++)
        z2_file.buttons_usable[i] = prevstates[i];

    // Restore modified fields
    z2_file.game_state = game_state;
    z2_file.pre_game_state = pre_game_state;
    z2_file.alpha_transition = alpha_transition;
    z2_file.sub_game_state = sub_game_state;
}

bool check_c_item_usable(u8 c) {
    bool dest[4];

    check_item_usability(dest, 0xFF, c, 0xFF, 0xFF);
    return dest[1];
}
