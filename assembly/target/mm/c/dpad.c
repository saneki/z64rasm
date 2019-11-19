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
static uint16_t position[2] = { 30, 60 };

// Positions of D-Pad item textures, relative to main texture.
static int16_t positions[4][2] = {
    { 1, -15 },
    { 15, 0 },
    { 1, 13 },
    { -14, 0 },
};

// Whether or not D-Pad items are usable, according to z64_UpdateButtonUsability.
static bool usable[4];

// Whether the previous frame was a "minigame" frame.
bool g_was_minigame = false;

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
    if (item == Z64_ITEM_NONE)
        return false;
    return get_slot(item, slot, (uint8_t *)&z64_file.items, sizeof(z64_file.items));
}

static bool get_mask_slot(uint8_t item, uint8_t *slot) {
    if (item == Z64_ITEM_NONE)
        return false;
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

static bool try_use_item(uint8_t slot, uint8_t item) {
    if (z64_file.items[slot] == item) {
        z64_UseItem(&z64_ctxt, &z64_link, item);
        return true;
    }

    return false;
}

static bool try_use_mask(uint8_t slot, uint8_t item) {
    // Can't use normal masks unless human link
    if (!IS_TRANSFORMATION_MASK(item) && z64_file.form != Z64_FORM_CHILD)
        return false;

    if (z64_file.masks[slot] == item) {
        z64_UseItem(&z64_ctxt, &z64_link, item);
        return true;
    }

    return false;
}

static bool try_use_item_or_mask(uint8_t item) {
    uint8_t slot;

    // Try to find slot in item or mask inventories
    if (!get_item_slot(item, &slot) && !get_mask_slot(item, &slot))
        return false;

    // If item value is in mask range, use mask. Otherwise default to use item.
    if (Z64_ITEM_DEKU_MASK <= item && item <= Z64_ITEM_GIANT_MASK) {
        return try_use_mask(slot, item);
    } else {
        return try_use_item(slot, item);
    }
}

static void get_dpad_item_usability(bool *dest)
{
    for (int i = 0; i < 4; i++)
        dest[i] = check_c_item_usable(DPAD_CONFIG[i]);
}

static bool check_action_state() {
    // Make sure certain action state flags are cleared before processing input
    if ((z64_link.action_state1 & DPAD_ACTION_STATE1) != 0)
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

static uint16_t update_y_position(uint16_t x, uint16_t y, uint16_t padding) {
    uint16_t heart_count = z64_file.hearts / 0x10;

    // Check if we have second row of hearts
    bool hearts = heart_count > 10;
    // Check if we have magic
    bool magic = z64_file.has_magic != 0;

    // If on left-half of screen
    if (x < 160) {
        // Calculate a minimum y position based on heart rows and magic
        // This is to avoid the D-Pad textures interfering with the hearts/magic UI
        uint16_t minimum = 50 + padding;
        if (hearts)
            minimum += 10;
        if (magic)
            minimum += 16;
        y = (y > minimum ? y : minimum);
    }

    return y;
}

bool is_minigame_frame()
{
    bool result = false;

    if (g_was_minigame)
        result = true;

    // Note on state 6:
    // If on Epona, and holding "B" for bow, then press "A" while holding "B", the game state
    // will go from: 0xC, 0x6, 0x32, 0xC. Thus we need to mark 0x6 as a "minigame frame" as well.
    // Riding Epona to a new area: 0xC, 0x32, 0x6, 0x1, 0x1...
    //
    // Note on state 1 (transition):
    // In the Deku playground, can go from 0xC to 0x1 when cutscene-transitioning to the business scrub.
    // Thus, if the minigame state goes directly to the transition state, consider that a minigame frame.
    g_was_minigame = (z64_file.game_state == Z64_GAME_STATE_MINIGAME ||
                      (g_was_minigame && z64_file.game_state == Z64_GAME_STATE_TRANSITION) ||
                      z64_file.game_state == 6);
    return result || g_was_minigame;
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

void do_dpad_per_game_frame()
{
    // If disabled, do nothing
    if (DPAD_STATE == DPAD_STATE_TYPE_DISABLED)
        return;

    // Update usability flags for later use in draw_dpad
    get_dpad_item_usability(usable);
}

bool handle_dpad() {
    pad_t pad_pressed = z64_ctxt.input[0].pad_pressed;

    // If disabled, do nothing
    if (DPAD_STATE == DPAD_STATE_TYPE_DISABLED)
        return false;

    // Check general game state to know if we can use C buttons at all
    // Note: After collecting a stray fairy (and possibly in other cases) the state flags are set
    // to 0 despite the game running normally.
    if (z64_file.game_state != Z64_GAME_STATE_NORMAL &&
        z64_file.game_state != Z64_GAME_STATE_BLACK_SCREEN)
        return false;

    // Check action state flags
    if (!check_action_state())
        return false;

    if (pad_pressed.du && usable[0]) {
        return try_use_item_or_mask(DPAD_CONFIG[0]);
    } else if (pad_pressed.dr && usable[1]) {
        return try_use_item_or_mask(DPAD_CONFIG[1]);
    } else if (pad_pressed.dd && usable[2]) {
        return try_use_item_or_mask(DPAD_CONFIG[2]);
    } else if (pad_pressed.dl && usable[3]) {
        return try_use_item_or_mask(DPAD_CONFIG[3]);
    }

    return false;
}

static bool is_any_item_usable(uint8_t *dpad, bool *usable)
{
    for (int i = 0; i < 4; i++) {
        if (has_item_or_mask(dpad[i]) && usable[i])
            return true;
    }

    return false;
}

void draw_dpad() {
    // If disabled, don't draw
    if (DPAD_STATE == DPAD_STATE_TYPE_DISABLED)
        return;

    // If we don't have any D-Pad items, draw nothing
    if (!have_any(DPAD_CONFIG))
        return;

    // Check for minigame frame, and do nothing unless transitioning into minigame
    // In which case the C-buttons alpha will be used instead for fade-in
    if (is_minigame_frame() && z64_file.pre_game_state != Z64_GAME_STATE_MINIGAME)
        return;

    // Use minimap alpha by default for fading textures out
    uint8_t prim_alpha = z64_game.sub_169E8.minimap_alpha & 0xFF;
    // If in minigame, the C buttons fade out and so should the D-Pad
    if (z64_file.game_state == Z64_GAME_STATE_MINIGAME ||
        z64_file.game_state == Z64_GAME_STATE_BOAT_ARCHERY ||
        z64_file.game_state == Z64_GAME_STATE_SWORDSMAN_GAME ||
        is_minigame_frame())
        prim_alpha = z64_game.sub_169E8.c_left_button_alpha & 0xFF;

    // Check if any items shown on the D-Pad are usable
    // If none are, draw main D-Pad sprite faded
    if (!is_any_item_usable(DPAD_CONFIG, usable) && prim_alpha > 0x4A)
        prim_alpha = 0x4A;

    // Show faded while flying as a Deku
    if (((z64_link.action_state3 & Z64_ACTION_STATE3_DEKU_AIR) != 0) && prim_alpha > 0x4A)
        prim_alpha = 0x4A;

    // Main sprite position
    uint16_t x = position[0];
    uint16_t y = position[1];
    y = update_y_position(x, y, 10);

    z64_disp_buf_t *db = &(z64_ctxt.gfx->overlay);
    gSPDisplayList(db->p++, &setup_db);
    gDPPipeSync(db->p++);
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, prim_alpha);
    gDPSetCombineMode(db->p++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    sprite_load(db, &dpad_sprite, 0, 1);
    sprite_draw(db, &dpad_sprite, 0, x, y, 16, 16);

    for (int i = 0; i < 4; i++) {
        uint8_t value = DPAD_CONFIG[i];

        // Calculate x/y from relative positions
        uint16_t ix = x + positions[i][0];
        uint16_t iy = y + positions[i][1];

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
        sprite_draw(db, &dpad_item_sprites, 0, ix, iy, 16, 16);
    }

    gDPPipeSync(db->p++);
}
