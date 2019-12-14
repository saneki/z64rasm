#include "z64.h"

void * get_ram_from_gamestate_entry_vram(z64_gamestate_entry_t *gs, uint32_t vram) {
    if (gs->ram && gs->vram_start <= vram && vram < gs->vram_end) {
        uint32_t offset = vram - gs->vram_start;
        return (void *)((char *)gs->ram + offset);
    } else {
        return NULL;
    }
}

void * get_ram_from_player_ovl_vram(z64_player_ovl_table_t *ovl, uint32_t vram) {
    if (ovl->ram && ovl->vram_start <= vram && vram < ovl->vram_end) {
        uint32_t offset = vram - ovl->vram_start;
        return (void *)((char *)ovl->ram + offset);
    } else {
        return NULL;
    }
}