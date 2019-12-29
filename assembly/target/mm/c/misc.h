#ifndef MISC_H
#define MISC_H

#include <stdbool.h>
#include "z2.h"

enum pushblock_mode {
    PUSHBLOCK_MODE_DEFAULT,
    PUSHBLOCK_MODE_FAST,
    PUSHBLOCK_MODE_CUSTOM,
};

union hash {
    union {
        u8 primary[0x04];
        u32 value;
    };
    u8 full[0x10];
};

// Magic number for misc_config: "MISC"
#define MISC_CONFIG_MAGIC 0x4D495343

struct misc_config {
    u32 magic;              /* 0x0000 */
    u32 version;            /* 0x0004 */
    union hash hash;        /* 0x0008 */
    u8 ocarina_underwater;  /* 0x0018 */
    u8 pushblock_mode;      /* 0x0019 */
    u8 draw_hash;           /* 0x001A */
    u8 reserved;            /* 0x001B */
    f32 pushblock_speed;    /* 0x001C */
};                          /* 0x0020 */

bool misc_can_use_ocarina_underwater();
struct misc_config* misc_get_config();
f32 misc_get_push_block_speed(z2_actor_t *actor, z2_game_t *game);

#endif // MISC_H
