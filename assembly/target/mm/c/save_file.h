#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include "quest_item_storage.h"

#define SAVE_FILE_CONFIG_MAGIC 0x53415645

struct save_file_config {
    u32                       magic;                 /* 0x0000 */
    u32                       version;               /* 0x0004 */
    struct quest_item_storage quest_storage;         /* 0x0008 */
};                                                   /* 0x001A */

struct save_file_config* save_file_get_config(void);
struct quest_item_storage* save_file_get_quest_item_storage(void);

#endif // SAVE_FILE_H
