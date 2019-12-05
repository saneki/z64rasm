#include <stdbool.h>
#include "z64.h"

void draw_b_button_icon_color_fix(z64_game_t *game) {
    // Clear the Env color before drawing amounts/text
    z64_disp_buf_t *db = &(z64_ctxt.gfx->overlay);
    gDPSetEnvColor(db->p++, 0x00, 0x00, 0x00, 0xFF);

    z64_DrawBButtonIcon(game);
}

void draw_c_button_icons_color_fix(z64_game_t *game) {
    // Clear the Env color before drawing amounts/text
    z64_disp_buf_t *db = &(z64_ctxt.gfx->overlay);
    gDPSetEnvColor(db->p++, 0x00, 0x00, 0x00, 0xFF);

    z64_DrawCButtonIcons(game);
}
