#ifndef MISC_H
#define MISC_H

#include <stdbool.h>
#include "types.h"

// Magic number for misc_config: "MISC"
#define MISC_CONFIG_MAGIC 0x4D495343

struct misc_config {
    u32 magic;              /* 0x0000 */
    u32 version;            /* 0x0004 */
    u8 ocarina_underwater;  /* 0x0008 */
    u8 reserved[3];         /* 0x0009 */
};                          /* 0x000C */

bool misc_can_use_ocarina_underwater();

#endif // MISC_H
