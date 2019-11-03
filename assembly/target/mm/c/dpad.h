#ifndef DPAD_H
#define DPAD_H

// Most of these states get checked by the "UseItem" function itself.
// We do need to handle some of them though.
//
// Normally Z64_ACTION_STATE1_SPECIAL would not need to be checked, except for some rare cases
// (like exiting from the telescope).
#define DPAD_ACTION_STATE1 (      \
    Z64_ACTION_STATE1_SPECIAL |   \
    Z64_ACTION_STATE1_CHARGE_SPIN \
)
#define DPAD_ACTION_STATE2 (     \
    Z64_ACTION_STATE2_CLIMBING | \
    Z64_ACTION_STATE2_DIVING   | \
    Z64_ACTION_STATE2_DIVING_2   \
)
#define DPAD_ACTION_STATE3 (   \
    Z64_ACTION_STATE3_ROLLING  \
)

typedef enum {
    DPAD_STATE_TYPE_DISABLED, // 0
    DPAD_STATE_TYPE_ENABLED,  // 1, enabled with DPAD_CONFIG values
    DPAD_STATE_TYPE_DEFAULTS, // 2, enabled with DPAD_DEFAULT values
} DPAD_STATE_TYPE;

void dpad_init();
void handle_dpad();
void draw_dpad();

#endif
