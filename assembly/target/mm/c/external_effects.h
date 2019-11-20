#ifndef EXTERNAL_EFFECTS_H
#define EXTERNAL_EFFECTS_H

#include <stdint.h>

// Magic number: "EXFX"
#define EXTERNAL_EFFECTS_MAGIC 0x45584658

typedef struct {
    uint32_t magic;
    uint32_t version;

    // Effects added in version 0
    uint8_t chateau;
    uint8_t fairy;
    uint8_t freeze;
    uint8_t ice_physics;
    uint8_t jinx;
    uint8_t no_z;
    uint8_t paper_link;
    uint8_t reverse_controls;
    uint8_t wallet_fill;
} external_effects_t;

void handle_external_effects();

#endif // EXTERNAL_EFFECTS_H
