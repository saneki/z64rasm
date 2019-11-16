#ifndef ACTOR_H
#define ACTOR_H

#include "z64.h"

z64_actor_t* spawn_actor(uint8_t type, z64_xyzf_t pos, z64_rot_t rot, uint32_t instance);

#endif // ACTOR_H
