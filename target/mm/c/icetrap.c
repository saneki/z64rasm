#include <stdbool.h>
#include "reloc.h"
#include "z64.h"

static uint8_t g_pending_freezes = 0;

bool icetrap_is_pending() {
    return g_pending_freezes > 0;
}

void push_pending_icetrap() {
    if (g_pending_freezes < 0xFF)
        g_pending_freezes += 1;
}

bool give_icetrap() {
    if ((z2_file.game_state == Z2_GAME_STATE_TRANSITION) ||
        (z2_file.game_state == Z2_GAME_STATE_TRANSITION_2) ||
        (z2_link.action_state1 & Z2_ACTION_STATE1_SPECIAL) != 0)
        return false;

    if (g_pending_freezes && z2_link.frozen_timer == 0) {
        g_pending_freezes -= 1;
        z2_LinkInvincibility(&z2_link, 0x14);
        z2_LinkDamage(&z2_game, &z2_link, Z2_DAMAGE_EFFECT_FREEZE, 0x40800000);
        return true;
    }

    return false;
}
