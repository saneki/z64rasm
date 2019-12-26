#include "misc.h"
#include "z2.h"

struct misc_config MISC_CONFIG = {
    .magic = MISC_CONFIG_MAGIC,
    .version = 0,
    .ocarina_underwater = 0,
    .pushblock_mode = PUSHBLOCK_MODE_FAST,
    .pushblock_speed = 2.0,
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
};

bool misc_can_use_ocarina_underwater() {
    return MISC_CONFIG.ocarina_underwater != 0;
}

f32 misc_get_push_block_speed(z2_actor_t *actor, z2_game_t *game) {
    switch (MISC_CONFIG.pushblock_mode) {
        case PUSHBLOCK_MODE_DEFAULT:
            return 2.0;
        case PUSHBLOCK_MODE_FAST:
            return 6.0;
        case PUSHBLOCK_MODE_CUSTOM:
        default:
            return MISC_CONFIG.pushblock_speed;
    }
}

void misc_get_iceblock_push_speed(z2_actor_t *actor, z2_game_t *game, struct iceblock_speed *dest) {
    switch (MISC_CONFIG.pushblock_mode) {
        case PUSHBLOCK_MODE_DEFAULT:
            dest->initial = 1.2;
            dest->additive = 2.8;
            break;
        case PUSHBLOCK_MODE_FAST:
        case PUSHBLOCK_MODE_CUSTOM:
        default:
            dest->initial = 3.6;
            dest->additive = 8.4;
            break;
    }
}

u32 misc_get_great_bay_temple_faucet_speed(z2_actor_t *actor, z2_game_t *game) {
    union faucet_speed result;
    switch (MISC_CONFIG.pushblock_mode) {
        case PUSHBLOCK_MODE_DEFAULT:
            result.acceleration = 1;
            result.max_velocity = 5;
        case PUSHBLOCK_MODE_FAST:
        case PUSHBLOCK_MODE_CUSTOM:
        default:
            result.acceleration = 2;
            result.max_velocity = 0x31;
    }
    return result.all;
}
