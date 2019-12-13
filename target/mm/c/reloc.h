#ifndef RELOC_H
#define RELOC_H

#include "z64.h"

#define GET_RELOC_FUNC(NAME, OVL) ((NAME##_proc)get_ram_from_player_ovl_vram(&OVL, NAME##_vram))
#define GET_RELOC_PAUSE_FUNC(NAME)  GET_RELOC_FUNC(NAME, z64_0x801D0B70.pause_ovl)
#define GET_RELOC_PLAYER_FUNC(NAME) GET_RELOC_FUNC(NAME, z64_0x801D0B70.player_ovl)

/* Relocatable player functions */
#define z64_LinkDamage        GET_RELOC_PLAYER_FUNC(z64_LinkDamage)
#define z64_LinkInvincibility GET_RELOC_PLAYER_FUNC(z64_LinkInvincibility)
#define z64_UseItem           GET_RELOC_PLAYER_FUNC(z64_UseItem)

void * get_ram_from_player_ovl_vram(z64_player_ovl_table_t *ovl, uint32_t vram);

#endif // RELOC_H
