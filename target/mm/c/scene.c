#include "actor_ext.h"
#include "z2.h"

/**
 * Hook function used after the scene initialize function has been called.
 **/
void scene_after_init(z2_game_t *game) {
    // Set all actor ext heap entries to clear
    actor_ext_clear();
}
