#include "quest_item_storage.h"
#include "save_file.h"

static void save_file_init_struct(struct save_file_config *config) {
    config->magic = SAVE_FILE_CONFIG_MAGIC;
    config->version = 0;
    quest_item_storage_clear(&config->quest_storage);
}

void save_file_init(void) {
    if (SAVE_FILE_CONFIG.magic != SAVE_FILE_CONFIG_MAGIC) {
        save_file_init_struct(&SAVE_FILE_CONFIG);
    }
}
