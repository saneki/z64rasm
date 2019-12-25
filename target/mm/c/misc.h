#ifndef MISC_H
#define MISC_H

#include <stdbool.h>
#include "z2.h"

enum pushblock_mode {
    PUSHBLOCK_MODE_DEFAULT,
    PUSHBLOCK_MODE_FAST,
    PUSHBLOCK_MODE_CUSTOM,
};

// Magic number for misc_config: "MISC"
#define MISC_CONFIG_MAGIC 0x4D495343

struct misc_config {
    u32 magic;              /* 0x0000 */
    u32 version;            /* 0x0004 */
    u8 ocarina_underwater;  /* 0x0008 */
    u8 pushblock_mode;      /* 0x0009 */
    u8 reserved[2];         /* 0x000A */
    f32 pushblock_speed;    /* 0x000C */
};                          /* 0x0010 */

bool misc_can_use_ocarina_underwater();
f32 misc_get_push_block_speed(z2_actor_t *actor, z2_game_t *game);

#endif // MISC_H
