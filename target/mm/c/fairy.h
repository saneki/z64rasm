#ifndef FAIRY_H
#define FAIRY_H

#include <stdbool.h>
#include "z64.h"

bool can_interact_with_fairy();
bool get_next_fairy_instance(uint16_t *inst);
void reset_fairy_instance_usage();
z64_actor_t* spawn_next_fairy_actor(z64_xyzf_t pos);

#endif // FAIRY_H
