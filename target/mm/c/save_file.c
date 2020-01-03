#include "save_file.h"

struct save_file_config SAVE_FILE_CONFIG = {
    .magic = SAVE_FILE_CONFIG_MAGIC,
    .version = 0,
};

struct save_file_config* save_file_get_config(void) {
    return &SAVE_FILE_CONFIG;
}

struct quest_item_storage* save_file_get_quest_item_storage(void) {
    return &(SAVE_FILE_CONFIG.quest_storage);
}
