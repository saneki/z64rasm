#include "z64.h"

void * get_ram_from_player_ovl(z64_player_ovl_table_t *ovl, uint32_t offset) {
    if (ovl->ram) {
        return (void *)((char *)ovl->ram + offset);
    } else {
        return NULL;
    }
}
