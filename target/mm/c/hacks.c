#include <stdbool.h>
#include "z64.h"

static bool g_is_hovering = false;
static uint8_t g_reset_magic = 1;

static void fix_deku_hover_button_fade() {
    // This is a very hacky fix for specific magic flag messing up C-button "usability" (meaning
    // whether or not the C button is faded).
    //
    // It seems to mess up how C buttons are displayed while hovering using a Deku flower. Certain
    // items will not be faded out even though they are unusable. By extension, this affects
    // whether or not the D-Pad item textures are correctly faded when Deku hovering.
    //
    // Note: The purpose of the flag seems to be to reset the has_magic flag to 0x01 if it is 0x00.
    // However, I don't think it is actually used after has_magic is set. Thus if has_magic is
    // already set, disable reset_magic to fix the buggy behaviour. This also fixes the C buttons.
    //
    // Additional note: This is used after restoring from a save, so we need to preserve it.
    if (z64_file.has_magic != 0) {
        // This hack disables the reset_magic flag specifically when Deku hovering, then re-enables
        // it afterwards.
        if ((z64_link.action_state3 & Z64_ACTION_STATE3_DEKU_AIR) != 0) {
            if (!g_is_hovering) {
                // If Deku hovering, set reset_magic to 0
                g_reset_magic = z64_file.reset_magic;
                z64_file.reset_magic = 0;
                g_is_hovering = true;
            }
        } else {
            if (g_is_hovering) {
                // If not Deku hovering, restore reset_magic to previous value
                z64_file.reset_magic = g_reset_magic;
                g_is_hovering = false;
            }
        }
    }
}

void do_hacks_per_game_frame() {
    fix_deku_hover_button_fade();
}
