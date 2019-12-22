#include <stdbool.h>
#include "z2.h"

static bool g_override_floor_physics_type = false;
static u32 g_override_floor_physics_type_value = 0;

void override_floor_physics_type(bool enabled, u32 type) {
    g_override_floor_physics_type = enabled;
    g_override_floor_physics_type_value = type;
}

u32 override_get_floor_physics_type(void *arg0, void *arg1, u8 arg2) {
    if (g_override_floor_physics_type)
        return g_override_floor_physics_type_value;
    else
        return z2_GetFloorPhysicsType(arg0, arg1, arg2);
}
