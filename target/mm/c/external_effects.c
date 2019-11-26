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
    .camera_overlook = 0,
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

// Specifies camera states that can be changed via an effect.
static const bool g_freecam_modes[0x5B] = {
    1, // 0x00 NONE
    1, // 0x01 NORMAL0
    1, // 0x02 NORMAL3
    1, // 0x03 CIRCLE5
    1, // 0x04 HORSE0
    1, // 0x05 ZORA0
    1, // 0x06 PREREND0
    1, // 0x07 PREREND1
    1, // 0x08 DOORC
    1, // 0x09 DEMO0
    1, // 0x0A FREE0
    1, // 0x0B FUKAN0
    1, // 0x0C NORMAL1
    1, // 0x0D NANAME
    1, // 0x0E CIRCLE0
    1, // 0x0F FIXED0
    1, // 0x10 SPIRAL
    1, // 0x11 DUNGEON0
    1, // 0x12 ITEM0
    1, // 0x13 ITEM1
    1, // 0x14 ITEM2
    1, // 0x15 ITEM3
    1, // 0x16 NAVI
    1, // 0x17 WARP0
    1, // 0x18 DEATH
    1, // 0x19 REBIRTH
    1, // 0x1A TREASURE
    1, // 0x1B TRANSFORM
    1, // 0x1C ATTENTION
    1, // 0x1D WARP1
    1, // 0x1E DUNGEON1
    1, // 0x1F FIXED1
    1, // 0x20 FIXED2
    1, // 0x21 MAZE
    1, // 0x22 REMOTEBOMB
    1, // 0x23 CIRCLE1
    1, // 0x24 CIRCLE2
    1, // 0x25 CIRCLE3
    1, // 0x26 CIRCLE4
    1, // 0x27 FIXED3
    1, // 0x28 TOWER0
    1, // 0x29 PARALLEL0
    1, // 0x2A NORMALD
    1, // 0x2B SUBJECTD
    1, // 0x2C START0
    1, // 0x2D START2
    1, // 0x2E STOP0
    1, // 0x2F JCRUISING
    1, // 0x30 CLIMEMAZE
    1, // 0x31 SIDED
    1, // 0x32 DUNGEON2
    1, // 0x33 BOSS_SHIGE
    1, // 0x34 KEEPBACK
    1, // 0x35 CIRCLE6
    1, // 0x36 CIRCLE7
    1, // 0x37 CHUBOSS
    1, // 0x38 RFIXED1
    1, // 0x39 TRESURE1
    1, // 0x3A BOMBBASKET
    1, // 0x3B CIRCLE8
    1, // 0x3C FUKAN1
    1, // 0x3D DUNGEON3
    1, // 0x3E TELESCOPE
    1, // 0x3F ROOM0
    1, // 0x40 RCIRC0
    1, // 0x41 CIRCLE9
    1, // 0x42 ONTHEPOLE
    1, // 0x43 INBUSH
    1, // 0x44 BOSS_LAST
    1, // 0x45 BOSS_INI
    1, // 0x46 BOSS_HAK
    1, // 0x47 BOSS_KON
    1, // 0x48 CONNECT0
    1, // 0x49 MORAY
    1, // 0x4A NORMAL2
    1, // 0x4B BOMBBOWL
    1, // 0x4C CIRCLEa
    1, // 0x4D WHIRLPOOL
    1, // 0x4E KOKKOGAME
    1, // 0x4F GIANT
    1, // 0x50 SCENE0
    1, // 0x51 ROOM1
    1, // 0x52 WATER2
    1, // 0x53 SOKONASI
    1, // 0x54 FORCEKEEP
    1, // 0x55 PARALLEL1
    1, // 0x56 START1
    1, // 0x57 ROOM2
    1, // 0x58 NORMAL4
    1, // 0x59 SHELL
    1, // 0x5A DUNGEON4
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

static void handle_camera_overlook_effect() {
    // Handle "Camera Overlook" effect.
    if (g_external_effects.camera_fukan) {
        int16_t curstate = z64_game.cameras[0].state;
        if (g_freecam_modes[curstate] && curstate != Z64_CAMERA_STATE_FUKAN1) {
            z64_game.cameras[0].state = Z64_CAMERA_STATE_FUKAN1;

            // Camera mode used while Z-targetting, it should trigger the camera to begin drifting over Link
            z64_game.cameras[0].mode = Z64_CAMERA_MODE_PARALLEL;
        }
    }
}

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
    handle_camera_overlook_effect();
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
