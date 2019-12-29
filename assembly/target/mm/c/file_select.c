#include "gfx.h"
#include "hud_colors.h"
#include "misc.h"
#include "util.h"
#include "z2.h"

// Enables using Z to refresh file select hash icons.
// #define FILE_HASH_DEBUG

#define ITEM_TEXTURE_LEN 0x1000

// Sprite buffer for hash icon textures.
static sprite_t g_file_hash_item_sprites = {
    NULL, 32, 32, 4,
    G_IM_FMT_RGBA, G_IM_SIZ_32b, 4
};

// Number of icons to display using hash value.
const static int g_icon_count = 5;

// Texture indexes to use for hash icons.
static const u8 g_hash_icons[0x40] = {
    Z2_ITEM_OCARINA,
    Z2_ITEM_BOW,
    Z2_ITEM_FIRE_ARROW,
    Z2_ITEM_ICE_ARROW,
    Z2_ITEM_LIGHT_ARROW,
    Z2_ITEM_BOMB,
    Z2_ITEM_BOMBCHU,
    Z2_ITEM_DEKU_STICK,
    Z2_ITEM_DEKU_NUT,
    Z2_ITEM_MAGIC_BEAN,
    Z2_ITEM_POWDER_KEG,
    Z2_ITEM_PICTOGRAPH,
    Z2_ITEM_LENS,
    Z2_ITEM_HOOKSHOT,
    Z2_ITEM_FAIRY_SWORD,
    Z2_ITEM_EMPTY_BOTTLE,
    Z2_ITEM_DEKU_PRINCESS,
    Z2_ITEM_BUGS,
    Z2_ITEM_BIG_POE,
    Z2_ITEM_HOT_WATER,
    Z2_ITEM_ZORA_EGG,
    Z2_ITEM_GOLD_DUST,
    Z2_ITEM_MUSHROOM,
    Z2_ITEM_SEAHORSE,
    Z2_ITEM_CHATEAU_ROMANI,
    Z2_ITEM_MOON_TEAR,
    Z2_ITEM_TOWN_DEED,
    Z2_ITEM_ROOM_KEY,
    Z2_ITEM_MAMA_LETTER,
    Z2_ITEM_KAFEI_LETTER,
    Z2_ITEM_PENDANT,
    Z2_ITEM_MAP,
    Z2_ITEM_DEKU_MASK,
    Z2_ITEM_GORON_MASK,
    Z2_ITEM_ZORA_MASK,
    Z2_ITEM_FIERCE_DEITY_MASK,
    Z2_ITEM_MASK_OF_TRUTH,
    Z2_ITEM_KAFEI_MASK,
    Z2_ITEM_ALL_NIGHT_MASK,
    Z2_ITEM_BUNNY_HOOD,
    Z2_ITEM_KEATON_MASK,
    Z2_ITEM_GARO_MASK,
    Z2_ITEM_ROMANI_MASK,
    Z2_ITEM_CIRCUS_LEADER_MASK,
    Z2_ITEM_POSTMAN_HAT,
    Z2_ITEM_COUPLE_MASK,
    Z2_ITEM_GREAT_FAIRY_MASK,
    Z2_ITEM_GIBDO_MASK,
    Z2_ITEM_DON_GERO_MASK,
    Z2_ITEM_KAMARO_MASK,
    Z2_ITEM_CAPTAIN_HAT,
    Z2_ITEM_STONE_MASK,
    Z2_ITEM_BREMEN_MASK,
    Z2_ITEM_BLAST_MASK,
    Z2_ITEM_MASK_OF_SCENTS,
    Z2_ITEM_GIANT_MASK,
    Z2_ITEM_KOKIRI_SWORD,
    Z2_ITEM_GILDED_SWORD,
    Z2_ITEM_HELIX_SWORD,
    Z2_ITEM_HERO_SHIELD,
    Z2_ITEM_MIRROR_SHIELD,
    Z2_ITEM_QUIVER_40,
    Z2_ITEM_ADULT_WALLET,
    0x61, // Bomber's Notebook
};

static void load_texture(u8 *buf, int idx, u8 item) {
    u32 phys = z2_GetFilePhysAddr(z2_item_texture_file);
    u8 *dest = buf + (idx * ITEM_TEXTURE_LEN);
    z2_LoadFileFromArchive(phys, item, dest, ITEM_TEXTURE_LEN);
}

static void update_textures(void *buf, int count, u32 hash) {
    for (int i = 0; i < count; i++, hash <<= 6) {
        u32 sym = (hash >> 26);
        u8 item = g_hash_icons[sym];
        load_texture(buf, i, item);
    }
}

void file_select_hook_after_ctor(z2_game_t *game) {
    // Allocate space for hash icon textures
    if (g_file_hash_item_sprites.buf == NULL) {
        g_file_hash_item_sprites.buf = heap_alloc(ITEM_TEXTURE_LEN * g_icon_count);
    }

    // Write icon textures
    void *buf = g_file_hash_item_sprites.buf;
    if (buf != NULL) {
        struct misc_config *config = misc_get_config();
        u32 hash = config->hash.value;
        update_textures(buf, g_icon_count, hash);
    }
}

void file_select_hook_after_dtor(z2_game_t *game) {
    // Todo: Properly unload textures when not needed?
}

void file_select_before_draw(z2_game_t *game) {
    // Update colors for HUD elements on file select
    hud_colors_main_menu_init();

#ifdef FILE_HASH_DEBUG
    // When pressing Z, update file hash to random new value
    void *buf = g_file_hash_item_sprites.buf;
    struct misc_config *config = misc_get_config();
    z2_pad_t pad_pressed = game->common.input[0].pad_pressed;
    if (pad_pressed.z && config->draw_hash && buf != NULL) {
        config->hash.value = z2_RngInt();
        update_textures(buf, g_icon_count, config->hash.value);
        z2_PlaySfx(0x483B);
    }
#endif
}

void file_select_draw_hash() {
    int icon_size = 24;
    int padding = 8;
    int width = (g_icon_count * icon_size) + ((g_icon_count - 1) * padding);
    int left = (Z2_SCREEN_WIDTH - width) / 2;
    int top = 12;

    // Generate next seed
    z2_RngInt();

    struct misc_config *config = misc_get_config();
    if (config->draw_hash) {
        z2_disp_buf_t *db = &(z2_game.common.gfx->poly_opa);

        // Call setup display list
        gSPDisplayList(db->p++, &setup_db);

        gDPPipeSync(db->p++);
        gDPSetCombineMode(db->p++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);

        for (int i = 0; i < g_icon_count; i++) {
            sprite_load(db, &g_file_hash_item_sprites, i, 1);
            sprite_draw(db, &g_file_hash_item_sprites, 0, left, top, icon_size, icon_size);
            left += icon_size + padding;
        }
    }
}
