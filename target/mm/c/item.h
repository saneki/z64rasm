#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>
#include <stdint.h>

bool check_c_item_usable(uint8_t c);
void check_item_usability(bool *dest, uint8_t b, uint8_t c1, uint8_t c2, uint8_t c3);

#endif // ITEM_H
