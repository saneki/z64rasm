#include <stdbool.h>
#include "quest_item_storage.h"
#include "save_file.h"
#include "z2.h"

static bool check_inventory_slot(u8 item, u8 slot) {
    if (z2_file.inventory[slot] == item) {
        return true;
    } else if (z2_file.inventory[slot] != Z2_ITEM_NONE) {
        struct quest_item_storage *storage = save_file_get_quest_item_storage();
        return quest_item_storage_has(storage, item);
    } else {
        return false;
    }
}

bool quest_items_door_check(z2_game_t *game, u8 item, u8 slot) {
    return check_inventory_slot(item, slot);
}

bool quest_items_time_tag_check(z2_actor_t *actor, z2_game_t *game, u8 item, u8 slot) {
    return check_inventory_slot(item, slot);
}
