#ifndef FLOOR_PHYSICS_H
#define FLOOR_PHYSICS_H

#include <stdbool.h>
#include "types.h"

void override_floor_physics_type(bool enabled, u32 type);
u32 override_get_floor_physics_type(void *arg0, void *arg1, u8 arg2);

#endif // FLOOR_PHYSICS_H
