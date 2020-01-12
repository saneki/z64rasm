#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include "quest_item_storage.h"
#include "z2.h"

#define SAVE_FILE_CONFIG_MAGIC 0x53415645

struct save_file_config {
    u32                       magic;                 /* 0x0000 */
    u32                       version;               /* 0x0004 */
    struct quest_item_storage quest_storage;         /* 0x0008 */
};                                                   /* 0x001A */

#define SAVE_FILE_RAM    (z2_file_addr + 0x1E00)
#define SAVE_FILE_CONFIG (*(struct save_file_config*) SAVE_FILE_RAM)

void save_file_init(void);

#endif // SAVE_FILE_H
