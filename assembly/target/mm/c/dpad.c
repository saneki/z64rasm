#include <stdbool.h>
#include "dpad.h"
#include "gfx.h"
#include "item.h"
#include "util.h"
#include "z64.h"

#define ITEM_TEXTURE_LEN 0x1000

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

// Textures buffer pointer.
static uint8_t *textures;

static sprite_t dpad_item_sprites = {
    NULL, 32, 32, 4,
    G_IM_FMT_RGBA, G_IM_SIZ_32b, 4
};

// Indicates which item textures are currently loaded into our buffer.
static uint8_t texture_items[4] = {
    Z64_ITEM_NONE,
    Z64_ITEM_NONE,
    Z64_ITEM_NONE,
    Z64_ITEM_NONE,
};

// Position of D-Pad texture.
static uint16_t position[2] = { 30, 84 };

// Positions of D-Pad item textures, relative to main texture.
static int16_t positions[4][2] = {
    { 1, -15 },
    { 15, 0 },
    { 1, 13 },
    { -14, 0 },
};

// Whether or not D-Pad items are usable, according to z64_UpdateButtonUsability.
static bool usable[4];

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

static bool has_item_or_mask(uint8_t item) {
    uint8_t slot;
    return (get_item_slot(item, &slot) || get_mask_slot(item, &slot));
}

static bool have_any(uint8_t *dpad) {
    for (int i = 0; i < 4; i++) {
        if (has_item_or_mask(dpad[i]))
            return true;
    }

    return false;
}

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

static void get_dpad_item_usability(bool *dest)
{
    check_item_usability(dest, 0xFF, DPAD_CONFIG[1], DPAD_CONFIG[2], DPAD_CONFIG[3]);
    dest[0] = check_c_item_usable(DPAD_CONFIG[0]);
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

static void load_texture(int idx, uint8_t item)
{
    uint32_t phys = z64_GetPhysicalAddrOfFile(z64_item_texture_file);
    uint8_t *dest = textures + (idx * ITEM_TEXTURE_LEN);
    z64_LoadItemTexture(phys, item, dest, ITEM_TEXTURE_LEN);
    texture_items[idx] = item;
}

void dpad_init() {
    // If using default values, overwrite DPAD_CONFIG with DPAD_DEFAULT
    if (DPAD_STATE == DPAD_STATE_TYPE_DEFAULTS) {
        for (int i = 0; i < 4; i++) {
            DPAD_CONFIG[i] = DPAD_DEFAULT[i];
        }
    }

    // Allocate space for textures
    textures = heap_alloc(ITEM_TEXTURE_LEN * 4);
    dpad_item_sprites.buf = textures;

    // Load textures
    for (int i = 0; i < 4; i++)
        load_texture(i, DPAD_CONFIG[i]);
}

void handle_dpad() {
    pad_t pad_pressed = z64_ctxt.input[0].pad_pressed;

    // Update usability flags for later use in draw_dpad
    get_dpad_item_usability(usable);

    // Check general game state to know if we can use C buttons at all
    // Note: After collecting a stray fairy (and possibly in other cases) the state flags are set
    // to 0 despite the game running normally.
    if (z64_file.game_state != Z64_GAME_STATE_NORMAL &&
        z64_file.game_state != Z64_GAME_STATE_BLACK_SCREEN)
        return;

    // Check action state flags
    if (!check_action_state())
        return;

    if (DPAD_STATE != DPAD_STATE_TYPE_DISABLED) {
        if (pad_pressed.du && usable[0]) {
            try_use_item_or_mask(DPAD_CONFIG[0]);
        } else if (pad_pressed.dr && usable[1]) {
            try_use_item_or_mask(DPAD_CONFIG[1]);
        } else if (pad_pressed.dd && usable[2]) {
            try_use_item_or_mask(DPAD_CONFIG[2]);
        } else if (pad_pressed.dl && usable[3]) {
            try_use_item_or_mask(DPAD_CONFIG[3]);
        }
    }
}

void draw_dpad() {
    // If disabled, don't draw
    if (DPAD_STATE == DPAD_STATE_TYPE_DISABLED)
        return;

    // If we don't have any D-Pad items, draw nothing
    if (!have_any(DPAD_CONFIG))
        return;

    // Use minimap alpha by default for fading textures out
    uint8_t prim_alpha = z64_game.sub_169E8.minimap_alpha & 0xFF;
    // If in minigame, the C buttons fade out and so should the D-Pad
    if (z64_file.game_state == Z64_GAME_STATE_MINIGAME ||
        z64_file.game_state == Z64_GAME_STATE_SWORDSMAN_GAME)
        prim_alpha = z64_game.sub_169E8.c_left_button_alpha & 0xFF;

    uint16_t x = position[0], y = position[1];
    z64_disp_buf_t *db = &(z64_ctxt.gfx->overlay);
    gSPDisplayList(db->p++, &setup_db);
    gDPPipeSync(db->p++);
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, prim_alpha);
    gDPSetCombineMode(db->p++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    sprite_load(db, &dpad_sprite, 0, 1);
    sprite_draw(db, &dpad_sprite, 0, x, y, 16, 16);

    for (int i = 0; i < 4; i++) {
        uint16_t ix = positions[i][0], iy = positions[i][1];
        uint8_t value = DPAD_CONFIG[i];

        // Show nothing if not in inventory
        if (!has_item_or_mask(value))
            continue;

        // Draw faded
        uint8_t alpha = prim_alpha;
        if (!usable[i] && alpha > 0x4A)
            alpha = 0x4A;
        gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);

        // If D-Pad item has changed, load new texture on the fly.
        if (texture_items[i] != value) {
            load_texture(i, value);
        }

        sprite_load(db, &dpad_item_sprites, i, 1);
        sprite_draw(db, &dpad_item_sprites, 0, x + ix, y + iy, 16, 16);
    }

    gDPPipeSync(db->p++);
}
