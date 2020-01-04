#ifndef QUEST_ITEMS_H
#define QUEST_ITEMS_H

#include "z2.h"

// Check if an inventory slot is a quest items slot.
#define IS_QUEST_SLOT(S) ((S) == Z2_SLOT_QUEST1 || (S) == Z2_SLOT_QUEST2 || (S) == Z2_SLOT_QUEST3)

void quest_items_after_receive(u8 item);
void quest_items_after_removal(u8 item, u8 slot);

#endif // QUEST_ITEMS_H
