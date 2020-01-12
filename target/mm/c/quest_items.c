#include <stdbool.h>
#include "misc.h"
#include "quest_items.h"
#include "quest_item_storage.h"
#include "save_file.h"
#include "z2.h"

static bool check_inventory_slot(u8 item, u8 slot) {
    if (z2_file.inventory[slot] == item) {
        return true;
    } else if (MISC_CONFIG.quest_item_storage && z2_file.inventory[slot] != Z2_ITEM_NONE) {
        return quest_item_storage_has(&SAVE_FILE_CONFIG.quest_storage, item);
    } else {
        return false;
    }
}

void quest_items_after_receive(u8 item) {
    // Try to add quest item to storage.
    quest_item_storage_put(&SAVE_FILE_CONFIG.quest_storage, item);
}

void quest_items_after_removal(u8 item, u8 slot) {
    struct quest_item_storage *storage = &SAVE_FILE_CONFIG.quest_storage;
    // Remove quest item from storage.
    if (quest_item_storage_remove(storage, item)) {
        // Set next item into inventory if any.
        if (MISC_CONFIG.quest_item_storage) {
            u8 next = quest_item_storage_next(storage, item);
            if (next != Z2_ITEM_NONE && IS_QUEST_SLOT(slot)) {
                z2_file.items[slot] = next;
            }
        }
    }
}

void quest_items_after_song_of_time_clear(void) {
    // After Song of Time, clear quest items in storage.
    quest_item_storage_clear(&SAVE_FILE_CONFIG.quest_storage);
}

bool quest_items_get_slot(int *slot, u8 item) {
    int sslot, idx;
    if (quest_item_storage_get_slot(&sslot, &idx, item)) {
        *slot = ((sslot + 1) * 6) - 1;
        return true;
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
