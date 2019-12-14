#ifndef MISC_H
#define MISC_H

#include <stdbool.h>
#include <stdint.h>

struct misc_config {
    uint32_t version;            /* 0x0000 */
    uint8_t ocarina_underwater;  /* 0x0004 */
    uint8_t reserved[3];         /* 0x0005 */
};                               /* 0x0008 */

bool misc_can_use_ocarina_underwater();

#endif // MISC_H
