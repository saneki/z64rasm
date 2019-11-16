#include "z64.h"

z64_actor_t* spawn_actor(uint8_t type, z64_xyzf_t pos, z64_rot_t rot, uint32_t instance) {
    void *arg0 = &(z64_game.unk_1CA0_);
    return z64_SpawnActor(arg0, &z64_game, type, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, instance);
}
