#ifndef ICETRAP_H
#define ICETRAP_H

#include <stdbool.h>
#include "z2.h"

bool give_icetrap(z2_link_t *link, z2_game_t *game);
bool icetrap_is_pending();
void push_pending_icetrap();

#endif // ICETRAP_H
