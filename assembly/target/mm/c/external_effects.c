#include <stdbool.h>
#include "external_effects.h"
#include "fairy.h"
#include "floor_physics.h"
#include "icetrap.h"
#include "z64.h"

// Fairy spawn cooldown (in frames).
#define FAIRY_COOLDOWN 0x10

// Maximum amount of fairies in queue.
#define FAIRY_MAX      12

// Jinx unit amount (multiplied by value in structure, then added to timer).
#define JINX_AMOUNT    0x100

// Maximum jinx timer value in memory.
#define JINX_MAX       0xFFFF

external_effects_t g_external_effects = {
    .magic = EXTERNAL_EFFECTS_MAGIC,
    .version = 0,
    .chateau = 0,
    .fairy = 0,
    .freeze = 0,
    .ice_physics = 0,
    .jinx = 0,
    .no_z = 0,
    .paper_link = 0,
    .reverse_controls = 0,
    .wallet_fill = 0,
};

// Whether or not to refill some magic on this frame.
static bool g_refill_magic = false;

// Whether or not we are in our special jinx state.
static bool g_jinxed = false;

// Previous jinx value in our special jinx state.
static uint16_t g_previous_jinx_value = 0;

// Cooldown for spawning fairies, in frames.
static uint32_t g_fairy_cooldown = 0;

// Most recent scene, tracked for fairy usage.
static uint16_t g_fairy_scene = 0;

static void handle_chateau_effect() {
    // Handle "Chateau" effect
    if (g_external_effects.chateau) {
        z64_file.infinite_magic = 1;
        g_refill_magic = true;
        g_external_effects.chateau = 0;
    }

    // Refill magic
    if (g_refill_magic) {
        uint8_t total = (uint8_t)z64_file.magic_meter_size;
        uint8_t remaining = total - z64_file.magic;

        // Increment by 2 magic points per frame
        if (remaining >= 2) {
            z64_file.magic += 2;
            z64_PlaySfx(0x401F);
        } else if (remaining == 1) {
            z64_file.magic += 1;
            z64_PlaySfx(0x401F);
        }

        // If full, stop refilling magic
        if (z64_file.magic >= total) {
            z64_file.magic = total; // Just in case
            g_refill_magic = false;
        }
    }
}

static void handle_fairy_effect() {
    // Reset fairy instance usages when scene changes
    if (z64_game.scene_number != g_fairy_scene) {
        reset_fairy_instance_usage();
        g_fairy_scene = z64_game.scene_number;
        g_fairy_cooldown = 0;
    }

    // Enforce a maximum of fairies in queue
    if (g_external_effects.fairy > FAIRY_MAX) {
        g_external_effects.fairy = FAIRY_MAX;
    }

    // Check state type to see if we can receive a fairy during this frame
    if (g_external_effects.fairy && g_fairy_cooldown == 0 && can_interact_with_fairy()) {
        // Spawn fairy on top of Link, and call the function to interact
        z64_actor_t *fairy = spawn_next_fairy_actor(z64_link.common.pos1);
        if (fairy) {
            if (fairy->Main != NULL) {
                fairy->Main(fairy, &z64_game);
            }
            g_fairy_cooldown = FAIRY_COOLDOWN;
            g_external_effects.fairy -= 1;
        }
    }

    // Decrement cooldown per frame
    if (g_fairy_cooldown > 0) {
        g_fairy_cooldown -= 1;
    }
}

static void handle_freeze_effect() {
    // Handle "Freeze" effect.
    if (g_external_effects.freeze) {
        push_pending_icetrap();
        g_external_effects.freeze = 0;
    }
}

static void handle_ice_physics_effect() {
    // Handle "Ice Physics" effect.
    if (g_external_effects.ice_physics) {
        override_floor_physics_type(true, Z64_FLOOR_PHYSICS_ICE);
    } else {
        override_floor_physics_type(false, 0);
    }
}

static void handle_jinx_effect() {
    // Handle "Jinx" effect.
    if (g_external_effects.jinx) {
        // Add multiple of JINX_AMOUNT to jinx timer
        uint32_t amount = g_external_effects.jinx * JINX_AMOUNT;
        uint32_t timer = z64_file.jinx_timer + amount;
        timer = (timer < JINX_MAX ? timer : JINX_MAX);
        z64_file.jinx_timer = (uint16_t)timer;

        g_external_effects.jinx = 0;
        g_jinxed = true;

        g_previous_jinx_value = z64_file.jinx_timer;
    }

    // This is a special jinx, players cannot Song of Storms out of it.
    if (g_jinxed) {
        // Calculate current expected jinx value
        uint16_t expected = 0;
        if (g_previous_jinx_value > 1) {
            expected = g_previous_jinx_value - 1;
        }

        // If actual value is less than expected, this means Song of Storms was played or went back in time.
        if (z64_file.jinx_timer < expected) {
            z64_file.jinx_timer = expected;
        } else if (z64_file.jinx_timer == 0) {
            // Once the timer hits 0, disable our special jinx state.
            g_jinxed = false;
        }

        g_previous_jinx_value = z64_file.jinx_timer;
    }
}

static void handle_no_z_effect() {
    // Handle "No Z" effect.
    if (g_external_effects.no_z) {
        z64_game.common.input[0].raw.pad.z = 0;
        z64_game.common.input[0].pad_pressed.z = 0;
    }
}

static void handle_paper_link_effect() {
    // Handle "Paper Link" effect.
    if (g_external_effects.paper_link) {
        z64_link.common.scale.x = 0.001;
    } else {
        z64_link.common.scale.x = 0.01;
    }
}

static void handle_reverse_controls_effect() {
    // Handle "Reverse Controls" effect.
    if (g_external_effects.reverse_controls) {
        z64_game.common.input[0].raw.x = -z64_game.common.input[0].raw.x;
        z64_game.common.input[0].raw.y = -z64_game.common.input[0].raw.y;
        z64_game.common.input[0].x_diff = -z64_game.common.input[0].x_diff;
        z64_game.common.input[0].y_diff = -z64_game.common.input[0].y_diff;
        z64_game.common.input[0].adjusted_x = -z64_game.common.input[0].adjusted_x;
        z64_game.common.input[0].adjusted_y = -z64_game.common.input[0].adjusted_y;
    }
}

static void handle_wallet_fill_effect() {
    // Handle "Wallet Fill" effect.
    if (g_external_effects.wallet_fill) {
        z64_file.rupee_timer = 0x7FFF;
        g_external_effects.wallet_fill = 0;
    }
}

void handle_external_effects() {
    handle_chateau_effect();
    handle_fairy_effect();
    handle_freeze_effect();
    handle_ice_physics_effect();
    handle_jinx_effect();
    handle_no_z_effect();
    handle_paper_link_effect();
    handle_reverse_controls_effect();
    handle_wallet_fill_effect();
}
