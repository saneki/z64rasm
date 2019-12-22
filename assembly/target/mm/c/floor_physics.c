#include <stdbool.h>
#include "z64.h"

static bool g_override_floor_physics_type = false;
static uint32_t g_override_floor_physics_type_value = 0;

void override_floor_physics_type(bool enabled, uint32_t type) {
    g_override_floor_physics_type = enabled;
    g_override_floor_physics_type_value = type;
}

uint32_t override_get_floor_physics_type(void *arg0, void *arg1, uint8_t arg2) {
    if (g_override_floor_physics_type)
        return g_override_floor_physics_type_value;
    else
        return z2_GetFloorPhysicsType(arg0, arg1, arg2);
}
