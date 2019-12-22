#ifndef MISC_H
#define MISC_H

#include <stdbool.h>
#include "types.h"

struct misc_config {
    u32 version;            /* 0x0000 */
    u8 ocarina_underwater;  /* 0x0004 */
    u8 reserved[3];         /* 0x0005 */
};                          /* 0x0008 */

bool misc_can_use_ocarina_underwater();

#endif // MISC_H
