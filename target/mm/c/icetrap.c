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
    if ((z64_file.game_state == Z64_GAME_STATE_TRANSITION) ||
        (z64_file.game_state == Z64_GAME_STATE_TRANSITION_2) ||
        (z64_link.action_state1 & Z64_ACTION_STATE1_SPECIAL) != 0)
        return false;

    if (g_pending_freezes && z64_link.frozen_timer == 0) {
        g_pending_freezes -= 1;
        GET_RELOC_PLAYER_FUNC(z64_LinkInvincibility);
        GET_RELOC_PLAYER_FUNC(z64_LinkDamage);
        z64_LinkInvincibility(&z64_link, 0x14);
        z64_LinkDamage(&z64_game, &z64_link, Z64_DAMAGE_EFFECT_FREEZE, 0x40800000);
        return true;
    }

    return false;
}
