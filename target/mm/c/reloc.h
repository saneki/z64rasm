#ifndef RELOC_H
#define RELOC_H

#include "z64.h"

#define GET_RELOC_FUNC(NAME, OVL) ((NAME##_proc)get_ram_from_player_ovl_vram(&OVL, NAME##_vram))
#define GET_RELOC_PAUSE_FUNC(NAME)  GET_RELOC_FUNC(NAME, z64_0x801D0B70.pause_ovl)
#define GET_RELOC_PLAYER_FUNC(NAME) GET_RELOC_FUNC(NAME, z64_0x801D0B70.player_ovl)

/* Macros for resolving RAM addresses from gamestate entries */
#define GET_GS_RELOC_TYPE(NAME, GS) (*(NAME##_t *)get_ram_from_gamestate_entry_vram(&(GS), (NAME##_vram)))

/* Relocatable player functions */
#define z64_LinkDamage        GET_RELOC_PLAYER_FUNC(z64_LinkDamage)
#define z64_LinkInvincibility GET_RELOC_PLAYER_FUNC(z64_LinkInvincibility)
#define z64_UseItem           GET_RELOC_PLAYER_FUNC(z64_UseItem)

/* Relocatable file select data */
#define z64_file_select_ctxt  GET_GS_RELOC_TYPE(z64_file_select_ctxt, z64_gamestate_table.file_select)

void * get_ram_from_gamestate_entry_vram(z64_gamestate_entry_t *gs, uint32_t vram);
void * get_ram_from_player_ovl_vram(z64_player_ovl_table_t *ovl, uint32_t vram);

#endif // RELOC_H
