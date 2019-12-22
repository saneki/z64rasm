#include "z64.h"

z2_actor_t* spawn_actor(uint8_t id, z2_xyzf_t pos, z2_rot_t rot, uint16_t var) {
    return z2_SpawnActor(&(z2_game.actor_ctxt), &z2_game, id, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, var);
}
