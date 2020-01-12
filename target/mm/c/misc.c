#include "misc.h"
#include "z2.h"

struct misc_config MISC_CONFIG = {
    .magic = MISC_CONFIG_MAGIC,
    .version = 0,
    .crit_wiggle = CRIT_WIGGLE_DEFAULT,
    .draw_hash = 1,
    .fast_push = 1,
    .ocarina_underwater = 1,
    .quest_item_storage = 1,
};

union faucet_speed {
    struct {
        u16 acceleration;
        u16 max_velocity;
    };
    u32 all;
};

struct iceblock_speed {
    f32 initial;
    f32 additive;
    f32 clamp;
};

struct misc_config* misc_get_config() {
    return &MISC_CONFIG;
}

bool misc_can_use_ocarina_underwater() {
    return MISC_CONFIG.ocarina_underwater != 0;
}

f32 misc_get_push_block_speed(z2_actor_t *actor, z2_game_t *game) {
    if (!MISC_CONFIG.fast_push) {
        return 2.0;
    } else {
        return 6.0;
    }
}

void misc_get_iceblock_push_speed(z2_actor_t *actor, z2_game_t *game, struct iceblock_speed *dest) {
    if (!MISC_CONFIG.fast_push) {
        dest->initial = 1.2;
        dest->additive = 2.8;
        dest->clamp = 3.5;
    } else {
        dest->initial = 3.6;
        dest->additive = 8.4;
        dest->clamp = 10.5;
    }
}

u32 misc_get_great_bay_temple_faucet_speed(z2_actor_t *actor, z2_game_t *game) {
    union faucet_speed result;
    if (!MISC_CONFIG.fast_push) {
        result.acceleration = 1;
        result.max_velocity = 5;
    } else {
        result.acceleration = 2;
        result.max_velocity = 0x31;
    }
    return result.all;
}

/**
 * Hook function to check whether or not to perform crit wiggle.
 **/
bool misc_crit_wiggle_check(z2_camera_t *camera, s16 health) {
    switch (MISC_CONFIG.crit_wiggle) {
        case CRIT_WIGGLE_ALWAYS_ON:
            return true;
        case CRIT_WIGGLE_ALWAYS_OFF:
            return false;
        case CRIT_WIGGLE_DEFAULT:
        default:
            return health <= 0x10;
    }
}
