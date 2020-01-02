#include "quest_item_storage.h"
#include "reloc.h"
#include "save_file.h"
#include "z2.h"

// Vertex buffers.
static Vtx g_vertex_bufs[(4 * 3) * 2];

// Vertex buffer pointers.
static Vtx* g_vertex[3] = {
    &g_vertex_bufs[(4 * 0) * 2],
    &g_vertex_bufs[(4 * 1) * 2],
    &g_vertex_bufs[(4 * 2) * 2],
};

static Vtx* get_vtx_buffer(z2_game_t *game, u32 vert_idx, int slot) {
    // Get vertex of current icon drawing to Item Select screen
    const Vtx *src_vtx = (game->pause_ctxt.vtx_buf + vert_idx);

    // Get dest Vtx (factor in frame counter)
    int framebufidx = (game->common.gfx->frame_cnt_1 & 1);
    Vtx *dst_vtx = g_vertex[slot] + (framebufidx * 4);

    // Copy source Vtx over to dest Vtx
    for (int i = 0; i < 4; i++) {
        dst_vtx[i] = src_vtx[i];
    }

    // Adjust X position
    dst_vtx[0].v.ob[0] += 0x10;
    dst_vtx[2].v.ob[0] += 0x10;

    // Adjust Y position
    dst_vtx[0].v.ob[1] -= 0x10;
    dst_vtx[1].v.ob[1] -= 0x10;

    return dst_vtx;
}

static void draw_icon(z2_gfx_t *gfx, const Vtx *vtx, u32 seg_addr, u16 width, u16 height, u16 qidx) {
    z2_disp_buf_t *db = &(gfx->poly_opa);
    // Instructions that happen before function
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, gfx->game->pause_ctxt.item_alpha & 0xFF);
    gSPVertex(db->p++, vtx, 4, 0); // Loads 4 vertices from RDRAM
    // Instructions that happen during function.
    gDPSetTextureImage(db->p++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, (void*)seg_addr);
    gDPSetTile(db->p++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
    gDPLoadSync(db->p++);
    gDPLoadBlock(db->p++, 7, 0, 0, 0x400 - 1, 0x80);
    gDPPipeSync(db->p++);
    gDPSetTile(db->p++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0);
    gDPSetTileSize(db->p++, 0, 0, 0, (width - 1) * 4, (height - 1) * 4);
    gSP1Quadrangle(db->p++, qidx + 0, qidx + 2, qidx + 3, qidx + 1, 0);
}

void pause_menu_item_select_draw_icon(z2_gfx_t *gfx, u8 item, u16 width, u16 height, u16 quad_idx, u32 vert_idx) {
    // Call original function to draw underlying item texture
    u32 orig_seg_addr = z2_item_segaddr_table[item];
    z2_PauseDrawItemIcon(gfx, orig_seg_addr, width, height, quad_idx);

    // If quest item storage, draw next quest item texture on bottom-right of current texture
    struct save_file_config *config = save_file_get_config();
    struct quest_item_storage *storage = &(config->quest_storage);
    if (quest_item_storage_has(storage, item)) {
        int slot, unused;
        u8 next = quest_item_storage_next(storage, item);
        if (next != Z2_ITEM_NONE && quest_item_storage_get_slot(&slot, &unused, next)) {
            u32 seg_addr = z2_item_segaddr_table[next];
            Vtx *vtx = get_vtx_buffer(gfx->game, vert_idx, slot);
            draw_icon(gfx, vtx, seg_addr, width, height, quad_idx);
        }
    }
}
