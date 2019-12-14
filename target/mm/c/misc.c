#include "misc.h"

struct misc_config MISC_CONFIG = {
    .version = 0,
    .ocarina_underwater = 0,
};

bool misc_can_use_ocarina_underwater() {
    return MISC_CONFIG.ocarina_underwater != 0;
}
