#include "misc.h"
#include "z2.h"

struct misc_config MISC_CONFIG = {
    .magic = MISC_CONFIG_MAGIC,
    .version = 0,
    .ocarina_underwater = 0,
    .pushblock_mode = PUSHBLOCK_MODE_FAST,
    .pushblock_speed = 2.0,
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
