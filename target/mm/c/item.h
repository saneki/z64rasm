#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>
#include "types.h"

bool check_c_item_usable(u8 c);
void check_item_usability(bool *dest, u8 b, u8 c1, u8 c2, u8 c3);

#endif // ITEM_H
