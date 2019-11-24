#include <stdbool.h>
#include "z64.h"

void draw_button_amounts_fix(z64_game_t *game, uint32_t arg1, uint16_t alpha) {
    // Clear the Env color before drawing amounts
    z64_disp_buf_t *db = &(z64_ctxt.gfx->overlay);
    gDPSetEnvColor(db->p++, 0x00, 0x00, 0x00, 0xFF);

    z64_DrawButtonAmounts(game, arg1, alpha);
}
