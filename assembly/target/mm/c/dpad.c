#include "z64.h"

#define IS_TRANSFORMATION_MASK(MASK)   \
    ((MASK) == Z64_ITEM_DEKU_MASK   || \
     (MASK) == Z64_ITEM_GORON_MASK  || \
     (MASK) == Z64_ITEM_ZORA_MASK   || \
     (MASK) == Z64_ITEM_FIERCE_DEITY_MASK)

static void try_use_item(uint8_t slot, uint8_t item) {
    if (z64_file.items[slot] == item) {
        z64_UseItem(&z64_ctxt, &z64_link, item);
    }
}

static void try_use_mask(uint8_t slot, uint8_t item) {
    // Can't use normal masks unless human link
    if (!IS_TRANSFORMATION_MASK(item) && z64_file.form != Z64_FORM_CHILD)
        return;

    if (z64_file.masks[slot] == item) {
        z64_UseItem(&z64_ctxt, &z64_link, item);
    }
}

void handle_dpad() {
    pad_t pad_pressed = z64_ctxt.input[0].pad_pressed;

    if (pad_pressed.dl) {
        try_use_mask(Z64_SLOT_GORON_MASK, Z64_ITEM_GORON_MASK);
    } else if (pad_pressed.dr) {
        try_use_mask(Z64_SLOT_ZORA_MASK, Z64_ITEM_ZORA_MASK);
    } else if (pad_pressed.du) {
        try_use_mask(Z64_SLOT_DEKU_MASK, Z64_ITEM_DEKU_MASK);
    } else if (pad_pressed.dd) {
        try_use_item(Z64_SLOT_OCARINA, Z64_ITEM_OCARINA);
    }
}

void draw_dpad() {
}
