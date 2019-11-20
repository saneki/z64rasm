#ifndef ICETRAP_H
#define ICETRAP_H

#include <stdbool.h>

bool give_icetrap();
bool icetrap_is_pending();
void push_pending_icetrap();

#endif // ICETRAP_H
