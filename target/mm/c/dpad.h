#ifndef DPAD_H
#define DPAD_H

typedef enum {
    DPAD_STATE_TYPE_DISABLED, // 0
    DPAD_STATE_TYPE_ENABLED,  // 1, enabled with DPAD_CONFIG values
    DPAD_STATE_TYPE_DEFAULTS, // 2, enabled with DPAD_DEFAULT values
} DPAD_STATE_TYPE;

void dpad_init();
void handle_dpad();
void draw_dpad();

#endif
