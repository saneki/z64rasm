#include <stdbool.h>
#include "z64.h"

void check_item_usability(bool *dest, uint8_t b, uint8_t c1, uint8_t c2, uint8_t c3) {
    uint8_t previous[4];

    // Backup
    previous[0] = z64_file.b_button;
    for (int i = 0; i < 3; i++)
        previous[i+1] = z64_file.c_buttons[i];

    z64_file.b_button = b;
    z64_file.c_buttons[0] = c1;
    z64_file.c_buttons[1] = c2;
    z64_file.c_buttons[2] = c3;

    z64_UpdateButtonUsability(&z64_ctxt);

    // Set dest to enabled-states (which are either 0x00 or 0xFF)
    dest[0] = (z64_file.b_button_usable == 0);
    for (int i = 0; i < 3; i++)
        dest[i+1] = (z64_file.c_buttons_usable[i] == 0);

    // Restore
    z64_file.b_button = previous[0];
    for (int i = 0; i < 3; i++)
        z64_file.c_buttons[i] = previous[i+1];

    // Todo: Restore usable state if needed?
}

bool check_c_item_usable(uint8_t c) {
    bool dest[4];

    check_item_usability(dest, 0xFF, c, 0xFF, 0xFF);
    return dest[1];
}
