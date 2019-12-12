#ifndef RELOC_H
#define RELOC_H

#include "z64.h"

#define GET_RELOC_FUNC(NAME, OVL) NAME##_proc NAME = get_ram_from_player_ovl(&OVL, NAME##_offset)
#define GET_RELOC_PLAYER_FUNC(NAME) GET_RELOC_FUNC(NAME, z64_0x801D0B70.player_ovl)

void * get_ram_from_player_ovl(z64_player_ovl_table_t *ovl, uint32_t offset);

#endif // RELOC_H
