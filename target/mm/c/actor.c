#include "z2.h"

z2_actor_t* actor_spawn(z2_game_t *game, u8 id, z2_xyzf_t pos, z2_rot_t rot, u16 var) {
    return z2_SpawnActor(&(game->actor_ctxt), game, id, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, var);
}
