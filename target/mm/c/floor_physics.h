#ifndef FLOOR_PHYSICS_H
#define FLOOR_PHYSICS_H

#include <stdbool.h>
#include <stdint.h>

void override_floor_physics_type(bool enabled, uint32_t type);
uint32_t override_get_floor_physics_type(void *arg0, void *arg1, uint8_t arg2);

#endif // FLOOR_PHYSICS_H
