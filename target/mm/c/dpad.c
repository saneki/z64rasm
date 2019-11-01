#include <stdbool.h>
#include "dpad.h"
#include "item.h"
#include "z64.h"

#define IS_TRANSFORMATION_MASK(MASK)   \
    ((MASK) == Z64_ITEM_DEKU_MASK   || \
     (MASK) == Z64_ITEM_GORON_MASK  || \
     (MASK) == Z64_ITEM_ZORA_MASK   || \
     (MASK) == Z64_ITEM_FIERCE_DEITY_MASK)

// D-Pad config values that can be set by a randomizer.
// Order: Up, Right, Down, Left
uint8_t DPAD_CONFIG[4] = {
    Z64_ITEM_NONE,
    Z64_ITEM_NONE,
    Z64_ITEM_NONE,
    Z64_ITEM_NONE,
};

// Default D-Pad values that will be used if config values undefined.
uint8_t DPAD_DEFAULT[4] = {
    Z64_ITEM_DEKU_MASK,
    Z64_ITEM_ZORA_MASK,
    Z64_ITEM_OCARINA,
    Z64_ITEM_GORON_MASK,
};

// State of D-pad usage (disabled, enabled, defaults).
uint8_t DPAD_STATE = DPAD_STATE_TYPE_DEFAULTS;

static bool get_slot(uint8_t item, uint8_t *slot, uint8_t *array, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        if (item == array[i]) {
            *slot = i;
            return true;
        }
    }

    return false;
}

static bool get_item_slot(uint8_t item, uint8_t *slot) {
    return get_slot(item, slot, (uint8_t *)&z64_file.items, sizeof(z64_file.items));
}

static bool get_mask_slot(uint8_t item, uint8_t *slot) {
    return get_slot(item, slot, (uint8_t *)&z64_file.masks, sizeof(z64_file.masks));
}

static void try_use_item(uint8_t slot, uint8_t item) {
    if (z64_file.items[slot] == item && check_c_item_usable(item)) {
        z64_UseItem(&z64_ctxt, &z64_link, item);
    }
}

static void try_use_mask(uint8_t slot, uint8_t item) {
    // Can't use normal masks unless human link
    if (!IS_TRANSFORMATION_MASK(item) && z64_file.form != Z64_FORM_CHILD)
        return;

    if (z64_file.masks[slot] == item && check_c_item_usable(item)) {
        z64_UseItem(&z64_ctxt, &z64_link, item);
    }
}

static void try_use_item_or_mask(uint8_t item) {
    uint8_t slot;

    // Try to find slot in item or mask inventories
    if (!get_item_slot(item, &slot) && !get_mask_slot(item, &slot))
        return;

    // If item value is in mask range, use mask. Otherwise default to use item.
    if (Z64_ITEM_DEKU_MASK <= item && item <= Z64_ITEM_GIANT_MASK) {
        try_use_mask(slot, item);
    } else {
        try_use_item(slot, item);
    }
}

static bool check_action_state() {
    // Make sure certain action state flags are cleared before processing input
    if ((z64_link.action_state1 & DPAD_ACTION_STATE1) != 0)
        return false;
    else if ((z64_link.action_state2 & DPAD_ACTION_STATE2) != 0)
        return false;
    else if ((z64_link.action_state3 & DPAD_ACTION_STATE3) != 0)
        return false;
    else
        return true;
}

void dpad_init() {
    // If using default values, overwrite DPAD_CONFIG with DPAD_DEFAULT
    if (DPAD_STATE == DPAD_STATE_TYPE_DEFAULTS) {
        for (int i = 0; i < 4; i++) {
            DPAD_CONFIG[i] = DPAD_DEFAULT[i];
        }
    }
}

void handle_dpad() {
    pad_t pad_pressed = z64_ctxt.input[0].pad_pressed;

    // Check general game state to know if we can use C buttons at all
    if (z64_file.game_state != Z64_GAME_STATE_NORMAL)
        return;

    // Check action state flags
    if (!check_action_state())
        return;

    if (DPAD_STATE != DPAD_STATE_TYPE_DISABLED) {
        if (pad_pressed.du) {
            try_use_item_or_mask(DPAD_CONFIG[0]);
        } else if (pad_pressed.dr) {
            try_use_item_or_mask(DPAD_CONFIG[1]);
        } else if (pad_pressed.dd) {
            try_use_item_or_mask(DPAD_CONFIG[2]);
        } else if (pad_pressed.dl) {
            try_use_item_or_mask(DPAD_CONFIG[3]);
        }
    }
}

void draw_dpad() {
}
