#ifndef Z64_H
#define Z64_H

#include <n64.h>
#include <stdint.h>
#include "color.h"

#define Z64_SCREEN_WIDTH         320
#define Z64_SCREEN_HEIGHT        240

#define Z64_TATL_NONE            0 // Tatl is not present
#define Z64_TATL_NORMAL          1

#define Z64_TIMESPEED_NORMAL     0
#define Z64_TIMESPEED_INVERTED   0xFFFFFFFE
#define Z64_TIMESPEED_STOP       0xFFFFFFFD

#define Z64_SAVETYPE_SONGOFTIME  0
#define Z64_SAVETYPE_OWL         1

#define Z64_MAGIC_NONE           0
#define Z64_MAGIC_NORMAL         0x30
#define Z64_MAGIC_FULL           0x60

#define IS_TRANSFORMATION_MASK(MASK)   \
    ((MASK) == Z64_ITEM_DEKU_MASK   || \
     (MASK) == Z64_ITEM_GORON_MASK  || \
     (MASK) == Z64_ITEM_ZORA_MASK   || \
     (MASK) == Z64_ITEM_FIERCE_DEITY_MASK)

/// Correlates to form field in z64_file_t.
typedef enum
{
    Z64_FORM_FIERCE_DEITY,
    Z64_FORM_GORON,
    Z64_FORM_ZORA,
    Z64_FORM_DEKU,
    Z64_FORM_CHILD,
} z64_form_t;

typedef enum
{
    // 0x00 (Inventory)
    Z64_ITEM_OCARINA,
    Z64_ITEM_BOW,
    Z64_ITEM_FIRE_ARROW,
    Z64_ITEM_ICE_ARROW,
    Z64_ITEM_LIGHT_ARROW,
    Z64_ITEM_FAIRY_OCARINA,
    Z64_ITEM_BOMB,
    Z64_ITEM_BOMBCHU,
    Z64_ITEM_DEKU_STICK,
    Z64_ITEM_DEKU_NUT,
    Z64_ITEM_MAGIC_BEAN,
    Z64_ITEM_SLINGSHOT,
    Z64_ITEM_POWDER_KEG,
    Z64_ITEM_PICTOGRAPH,
    Z64_ITEM_LENS,
    Z64_ITEM_HOOKSHOT,
    Z64_ITEM_FAIRY_SWORD,
    Z64_ITEM_HOOKSHOT_OOT,

    // 0x12 (Bottle)
    Z64_ITEM_EMPTY_BOTTLE,
    Z64_ITEM_RED_POTION,
    Z64_ITEM_GREEN_POTION,
    Z64_ITEM_BLUE_POTION,
    Z64_ITEM_FAIRY,
    Z64_ITEM_DEKU_PRINCESS,
    Z64_ITEM_MILK,
    Z64_ITEM_MILK_HALF,
    Z64_ITEM_FISH,
    Z64_ITEM_BUGS,
    Z64_ITEM_BLUE_FIRE,
    Z64_ITEM_POE,
    Z64_ITEM_BIG_POE,
    Z64_ITEM_WATER,
    Z64_ITEM_HOT_WATER,
    Z64_ITEM_ZORA_EGG,
    Z64_ITEM_GOLD_DUST,
    Z64_ITEM_MUSHROOM,
    Z64_ITEM_SEAHORSE,
    Z64_ITEM_CHATEAU_ROMANI,
    Z64_ITEM_EEL,
    Z64_ITEM_EMPTY_BOTTLE_2,

    // 0x28 (Quest)
    Z64_ITEM_MOON_TEAR,
    Z64_ITEM_TOWN_DEED,
    Z64_ITEM_SWAMP_DEED,
    Z64_ITEM_MOUNTAIN_DEED,
    Z64_ITEM_OCEAN_DEED,
    Z64_ITEM_ROOM_KEY,
    Z64_ITEM_MAMA_LETTER,
    Z64_ITEM_KAFEI_LETTER,
    Z64_ITEM_PENDANT,
    Z64_ITEM_MAP,

    // 0x32 (Masks)
    Z64_ITEM_DEKU_MASK,
    Z64_ITEM_GORON_MASK,
    Z64_ITEM_ZORA_MASK,
    Z64_ITEM_FIERCE_DEITY_MASK,
    Z64_ITEM_MASK_OF_TRUTH,
    Z64_ITEM_KAFEI_MASK,
    Z64_ITEM_ALL_NIGHT_MASK,
    Z64_ITEM_BUNNY_HOOD,
    Z64_ITEM_KEATON_MASK,
    Z64_ITEM_GARO_MASK,
    Z64_ITEM_ROMANI_MASK,
    Z64_ITEM_CIRCUS_LEADER_MASK,
    Z64_ITEM_POSTMAN_HAT,
    Z64_ITEM_COUPLE_MASK,
    Z64_ITEM_GREAT_FAIRY_MASK,
    Z64_ITEM_GIBDO_MASK,
    Z64_ITEM_DON_GERO_MASK,
    Z64_ITEM_KAMARO_MASK,
    Z64_ITEM_CAPTAIN_HAT,
    Z64_ITEM_STONE_MASK,
    Z64_ITEM_BREMEN_MASK,
    Z64_ITEM_BLAST_MASK,
    Z64_ITEM_MASK_OF_SCENTS,
    Z64_ITEM_GIANT_MASK,

    // 0x4A (???)
    Z64_ITEM_BOW_FIRE_ARROW,
    Z64_ITEM_BOW_ICE_ARROW,
    Z64_ITEM_BOW_LIGHT_ARROW,

    // 0x4D (Equipment)
    Z64_ITEM_KOKIRI_SWORD,
    Z64_ITEM_RAZOR_SWORD,
    Z64_ITEM_GILDED_SWORD,
    Z64_ITEM_HELIX_SWORD,
    Z64_ITEM_HERO_SHIELD,
    Z64_ITEM_MIRROR_SHIELD,
    Z64_ITEM_QUIVER_30,
    Z64_ITEM_QUIVER_40,
    Z64_ITEM_QUIVER_50,
    Z64_ITEM_BOMB_BAG_20,
    Z64_ITEM_BOMB_BAG_30,
    Z64_ITEM_BOMB_BAG_40,
    Z64_ITEM_WALLET_UNUSED,
    Z64_ITEM_ADULT_WALLET,
    Z64_ITEM_GIANT_WALLET,
    Z64_ITEM_FISHING_ROD,

    // 0x5D (Remains)
    Z64_ITEM_ODOLWA_REMAINS,
    Z64_ITEM_GOHT_REMAINS,
    Z64_ITEM_GYORG_REMAINS,
    Z64_ITEM_TWINMOLD_REMAINS,

    // 0x61 (Songs)
    Z64_ITEM_SONATA_OF_AWAKENING,
    Z64_ITEM_GORON_LULLABY,
    Z64_ITEM_NEW_WAVE_BOSSA_NOVA,
    Z64_ITEM_ELEGY_OF_EMPTINESS,
    Z64_ITEM_OATH_TO_ORDER,
    Z64_ITEM_SARIA_SONG,
    Z64_ITEM_SONG_OF_TIME,
    Z64_ITEM_SONG_OF_HEALING,
    Z64_ITEM_EPONA_SONG,
    Z64_ITEM_SONG_OF_SOARING,
    Z64_ITEM_SONG_OF_STORMS,
    Z64_ITEM_SUN_SONG,

    // 0x6D (Misc Equipment?)
    Z64_ITEM_BOMBER_NOTEBOOK,
    Z64_ITEM_HEART_PIECE = 0x7B,

    // 0x83 (Pickups)
    Z64_ITEM_HEART = 0x83,
    Z64_ITEM_GREEN_RUPEE,
    Z64_ITEM_BLUE_RUPEE,
    Z64_ITEM_RED_RUPEE = 0x87,
    Z64_ITEM_PURPLE_RUPEE,
    Z64_ITEM_SILVER_RUPEE,
    Z64_ITEM_PICKUP_DEKU_NUTS_10 = 0x8E,
    Z64_ITEM_PICKUP_ARROWS_10 = 0x93,
    Z64_ITEM_PICKUP_ARROWS_20,

    // 0xFF (None)
    Z64_ITEM_NONE = 0xFF,
} z64_item_t;

/// Item inventory slots.
typedef enum
{
    Z64_SLOT_OCARINA,
    Z64_SLOT_BOW,
    Z64_SLOT_FIRE_ARROW,
    Z64_SLOT_ICE_ARROW,
    Z64_SLOT_LIGHT_ARROW,
    Z64_SLOT_QUEST1,
    Z64_SLOT_BOMB,
    Z64_SLOT_BOMBCHU,
    Z64_SLOT_DEKU_STICK,
    Z64_SLOT_DEKU_NUT,
    Z64_SLOT_MAGIC_BEAN,
    Z64_SLOT_QUEST2,
    Z64_SLOT_POWDER_KEG,
    Z64_SLOT_PICTOGRAPH,
    Z64_SLOT_LENS,
    Z64_SLOT_HOOKSHOT,
    Z64_SLOT_FAIRY_SWORD,
    Z64_SLOT_QUEST3,
    Z64_SLOT_BOTTLE_1,
    Z64_SLOT_BOTTLE_2,
    Z64_SLOT_BOTTLE_3,
    Z64_SLOT_BOTTLE_4,
    Z64_SLOT_BOTTLE_5,
    Z64_SLOT_BOTTLE_6,
} z64_item_slot_t;

/// Mask inventory slots.
typedef enum
{
    Z64_SLOT_POSTMAN_HAT,
    Z64_SLOT_ALL_NIGHT_MASK,
    Z64_SLOT_BLAST_MASK,
    Z64_SLOT_STONE_MASK,
    Z64_SLOT_GREAT_FAIRY_MASK,
    Z64_SLOT_DEKU_MASK,
    Z64_SLOT_KEATON_MASK,
    Z64_SLOT_BREMEN_MASK,
    Z64_SLOT_BUNNY_HOOD,
    Z64_SLOT_DON_GERO_MASK,
    Z64_SLOT_MASK_OF_SCENTS,
    Z64_SLOT_GORON_MASK,
    Z64_SLOT_ROMANI_MASK,
    Z64_SLOT_CIRCUS_LEADER_MASK,
    Z64_SLOT_KAFEI_MASK,
    Z64_SLOT_COUPLE_MASK,
    Z64_SLOT_MASK_OF_TRUTH,
    Z64_SLOT_ZORA_MASK,
    Z64_SLOT_KAMARO_MASK,
    Z64_SLOT_GIBDO_MASK,
    Z64_SLOT_GARO_MASK,
    Z64_SLOT_CAPTAIN_HAT,
    Z64_SLOT_GIANT_MASK,
    Z64_SLOT_FIERCE_DEITY_MASK,
} z64_mask_slot_t;

typedef enum {
    Z64_GAME_STATE_BLACK_SCREEN,
    Z64_GAME_STATE_TRANSITION,
    // Postman's timing game.
    Z64_GAME_STATE_TRANSITION_2,
    Z64_GAME_STATE_DIALOGUE = 5,
    // Used when on Epona sometimes, for example holding B (bow) while pressing A ("Return").
    Z64_GAME_STATE_6 = 6,
    Z64_GAME_STATE_PAUSE = 7,
    Z64_GAME_STATE_ARCHERY_GAME = 8,
    Z64_GAME_STATE_MINIGAME = 0xC,
    Z64_GAME_STATE_SHOP = 0xF,
    Z64_GAME_STATE_ITEM_PROMPT = 0x10,
    // Boat cruise archery game.
    Z64_GAME_STATE_BOAT_ARCHERY = 0x11,
    // Honey & Darling minigame.
    Z64_GAME_STATE_HONEY_DARLING = 0x14,
    Z64_GAME_STATE_PICTOBOX = 0x15,
    Z64_GAME_STATE_SWORDSMAN_GAME = 0x16,
    Z64_GAME_STATE_NORMAL = 0x32,
} z64_game_state_t;

typedef enum {
    // NPC dialogue, get item, area transition, cutscene, form transition, using ocarina, etc.
    Z64_ACTION_STATE1_SPECIAL      = 0x20000000,
    // Form transition, using ocarina.
    Z64_ACTION_STATE1_SPECIAL_2    = 0x10000000,
    // Swimming.
    Z64_ACTION_STATE1_SWIM         = 0x08000000,
    // Damaged.
    Z64_ACTION_STATE1_DAMAGED      = 0x04000000,
    // Zora fins are out, "Put Away" may be prompted.
    Z64_ACTION_STATE1_ZORA_WEAPON  = 0x01000000,
    // On Epona.
    Z64_ACTION_STATE1_EPONA        = 0x00800000,
    // Shielding.
    Z64_ACTION_STATE1_SHIELD       = 0x00400000,
    // Using Zora fins.
    Z64_ACTION_STATE1_ZORA_FINS    = 0x00200000,
    // Aiming bow, hookshot, Zora fins, etc.
    Z64_ACTION_STATE1_AIM          = 0x00100000,
    // In the air (without jumping beforehand).
    Z64_ACTION_STATE1_FALLING      = 0x00080000,
    // In the air (with jumping beforehand).
    Z64_ACTION_STATE1_AIR          = 0x00040000,
    // In Z-target view.
    Z64_ACTION_STATE1_Z_VIEW       = 0x00020000,
    // Z-target check-able or speak-able.
    Z64_ACTION_STATE1_Z_CHECK      = 0x00010000,
    // Z-target enabled.
    Z64_ACTION_STATE1_Z_ON         = 0x00008000,
    // Hanging from ledge.
    Z64_ACTION_STATE1_LEDGE_HANG   = 0x00002000,
    // Charging spin attack.
    Z64_ACTION_STATE1_CHARGE_SPIN  = 0x00001000,
    // Hold above head.
    Z64_ACTION_STATE1_HOLD         = 0x00000800,
    // Hold new item over head.
    Z64_ACTION_STATE1_GET_ITEM     = 0x00000400,
    // Transition to day/night, Pictobox prompt.
    Z64_ACTION_STATE1_DAY_TRANS    = 0x00000200,
    // Dead.
    Z64_ACTION_STATE1_DEAD         = 0x00000080,
    // When walking in a cutscene? Unsure.
    // Used during Postman's minigame.
    Z64_ACTION_STATE1_MOVE_SCENE   = 0x00000020,
    // Zora electric barrier.
    Z64_ACTION_STATE1_BARRIER      = 0x00000010,
    // Item is out, may later prompt "Put Away."
    // Relevant to Bow, Hookshot, not Great Fairy Sword.
    Z64_ACTION_STATE1_ITEM_OUT     = 0x00000008,
    // Climbing ledge.
    Z64_ACTION_STATE1_LEDGE_CLIMB  = 0x00000004,
} z64_action_state1_t;

typedef enum {
    // Idle animation.
    Z64_ACTION_STATE2_IDLE         = 0x10000000,
    // Using ocarina? Maybe more.
    Z64_ACTION_STATE2_OCARINA      = 0x08000000,
    // Kamaro mask dance.
    Z64_ACTION_STATE2_KAMARO       = 0x02000000,
    // Can get down from Epona.
    Z64_ACTION_STATE2_CAN_DOWN     = 0x00400000,
    // Tatl C up button prompt.
    Z64_ACTION_STATE2_TATL_BUTTON  = 0x00200000,
    // When tatl is out.
    Z64_ACTION_STATE2_TATL_OUT     = 0x00100000,
    // Z-target jumping (sidehop, backflip).
    Z64_ACTION_STATE2_Z_JUMP       = 0x00080000,
    // Spin attack.
    Z64_ACTION_STATE2_SPIN_ATTACK  = 0x00020000,
    // Frozen, ends once ice cracks.
    Z64_ACTION_STATE2_FROZEN       = 0x00004000,
    // Stationary while climbing.
    Z64_ACTION_STATE2_CLIMB_STAY   = 0x00001000,
    // Diving.
    Z64_ACTION_STATE2_DIVING       = 0x00000800,
    // Diving, swimming as Zora.
    Z64_ACTION_STATE2_DIVING_2     = 0x00000400,
    // Grabbing onto a block.
    Z64_ACTION_STATE2_GRABBING     = 0x00000100,
    // Climbing. Also occurs during: transforming, hanging from ledge,
    // deku spinning, goron ball, sliding
    Z64_ACTION_STATE2_CLIMBING     = 0x00000040,
    // Running / moving.
    Z64_ACTION_STATE2_MOVING       = 0x00000020,
    // Pushing or pulling a block.
    Z64_ACTION_STATE2_PUSH_PULL    = 0x00000010,
    // Is set for some movement frames.
    Z64_ACTION_STATE2_MOVING_2     = 0x00000008,
    // "Check" or "Speak" prompt may appear.
    Z64_ACTION_STATE2_CHECK        = 0x00000002,
    // "Grab" prompt may appear.
    Z64_ACTION_STATE2_MAY_GRAB     = 0x00000001,
} z64_action_state2_t;

typedef enum {
    // Bremen mask march.
    Z64_ACTION_STATE3_BREMEN      = 0x20000000,
    // Rolling (non-Goron).
    Z64_ACTION_STATE3_ROLLING     = 0x08000000,
    // Attacking with sword, B button weapon.
    Z64_ACTION_STATE3_ATTACK      = 0x02000000,
    // Hover with flower petals? Maybe more.
    Z64_ACTION_STATE3_DEKU_AIR_2  = 0x01000000,
    // Deku hopping on water.
    Z64_ACTION_STATE3_DEKU_HOP    = 0x00200000,
    // Goron spike roll.
    Z64_ACTION_STATE3_GORON_SPIKE = 0x00080000,
    // Transforming (latter-half).
    Z64_ACTION_STATE3_TRANS_PART  = 0x00020000,
    // Zora swimming/diving.
    Z64_ACTION_STATE3_ZORA_SWIM   = 0x00008000,
    // Hover with flower petals.
    Z64_ACTION_STATE3_DEKU_AIR    = 0x00002000,
    // Jumping out of Deku flower.
    Z64_ACTION_STATE3_DEKU_RISE   = 0x00000200,
    // Deku flower dive.
    Z64_ACTION_STATE3_DEKU_DIVE   = 0x00000100,
    // Pull back bow string.
    Z64_ACTION_STATE3_PULL_BOW    = 0x00000040,
    // Post-attack.
    Z64_ACTION_STATE3_ATTACK_2    = 0x00000008,
    // Beginning of jump attack.
    Z64_ACTION_STATE3_JUMP_ATTACK = 0x00000002,
} z64_action_state3_t;

typedef enum {
    // Item "pickup", such as a rupee, arrows, magic, deku stick, etc.
    Z64_ACTOR_ID_PICKUP = 0xE,
    // Fairy.
    Z64_ACTOR_ID_FAIRY = 0x10,
} z64_actor_id_t;

typedef enum {
    // Step-on switches.
    Z64_ACTOR_TYPE_SWITCH,
    // Typically larger, more complex set pieces.
    Z64_ACTOR_TYPE_PROP,
    // Main player (Link).
    Z64_ACTOR_TYPE_PLAYER,
    // Bombs, Bombchus.
    Z64_ACTOR_TYPE_BOMB,
    // NPCs.
    Z64_ACTOR_TYPE_NPC,
    // Enemies, used for triggering room clear state.
    Z64_ACTOR_TYPE_ENEMY,
    Z64_ACTOR_TYPE_PROP2,
    Z64_ACTOR_TYPE_ITEM,
    Z64_ACTOR_TYPE_MISC,
    Z64_ACTOR_TYPE_BOSS,
    Z64_ACTOR_TYPE_DOOR,
    Z64_ACTOR_TYPE_CHEST,
} z64_actor_type_t;

typedef enum {
    Z64_FLOOR_TYPE_DIRT = 0,
    Z64_FLOOR_TYPE_SAND = 1,
    Z64_FLOOR_TYPE_STONE = 2,
    Z64_FLOOR_TYPE_WET1 = 4,
    Z64_FLOOR_TYPE_WET2 = 5,
    Z64_FLOOR_TYPE_PLANTS = 6,
    Z64_FLOOR_TYPE_GRASS = 8,
    Z64_FLOOR_TYPE_WOOD = 0xA,
    Z64_FLOOR_TYPE_SNOW = 0xE,
    Z64_FLOOR_TYPE_ICE = 0xF,
} z64_floor_type_t;

typedef enum {
    Z64_FLOOR_PHYSICS_NORMAL = 0,
    Z64_FLOOR_PHYSICS_ICE = 5,
    Z64_FLOOR_PHYSICS_SNOW = 0xE,
} z64_floor_physics_t;

typedef enum {
    // Damaged normally.
    Z64_DAMAGE_EFFECT_NORMAL = 0,
    // Flies backwards screaming.
    Z64_DAMAGE_EFFECT_FLY_BACK = 1,
    // Flies backwards.
    Z64_DAMAGE_EFFECT_FLY_BACK_2 = 2,
    // Freezes.
    Z64_DAMAGE_EFFECT_FREEZE = 3,
    // Electrocutes.
    Z64_DAMAGE_EFFECT_ELECTRIC = 4,
} z64_damage_effect_t;

// Source: https://wiki.cloudmodding.com/mm/Notes:Mini-Cutscenes#0x02
// More specifically, strings are in Yaz0 chunk in 0xBB1320 in debug ROM.
typedef enum {
    Z64_CAMERA_STATE_NONE,
    Z64_CAMERA_STATE_NORMAL0,
    Z64_CAMERA_STATE_NORMAL3,
    Z64_CAMERA_STATE_CIRCLE5,
    Z64_CAMERA_STATE_HORSE0,
    Z64_CAMERA_STATE_ZORA0,
    Z64_CAMERA_STATE_PREREND0,
    Z64_CAMERA_STATE_PREREND1,
    Z64_CAMERA_STATE_DOORC,
    Z64_CAMERA_STATE_DEMO0,
    Z64_CAMERA_STATE_FREE0,
    Z64_CAMERA_STATE_FUKAN0,
    Z64_CAMERA_STATE_NORMAL1,
    Z64_CAMERA_STATE_NANAME,
    Z64_CAMERA_STATE_CIRCLE0,
    Z64_CAMERA_STATE_FIXED0,
    Z64_CAMERA_STATE_SPIRAL,
    Z64_CAMERA_STATE_DUNGEON0,
    Z64_CAMERA_STATE_ITEM0,
    Z64_CAMERA_STATE_ITEM1,
    Z64_CAMERA_STATE_ITEM2,
    Z64_CAMERA_STATE_ITEM3,
    Z64_CAMERA_STATE_NAVI,
    Z64_CAMERA_STATE_WARP0,
    Z64_CAMERA_STATE_DEATH,
    Z64_CAMERA_STATE_REBIRTH,
    Z64_CAMERA_STATE_TREASURE,
    Z64_CAMERA_STATE_TRANSFORM,
    Z64_CAMERA_STATE_ATTENTION,
    Z64_CAMERA_STATE_WARP1,
    Z64_CAMERA_STATE_DUNGEON1,
    Z64_CAMERA_STATE_FIXED1,
    Z64_CAMERA_STATE_FIXED2,
    Z64_CAMERA_STATE_MAZE,
    Z64_CAMERA_STATE_REMOTEBOMB,
    Z64_CAMERA_STATE_CIRCLE1,
    Z64_CAMERA_STATE_CIRCLE2,
    Z64_CAMERA_STATE_CIRCLE3,
    Z64_CAMERA_STATE_CIRCLE4,
    Z64_CAMERA_STATE_FIXED3,
    Z64_CAMERA_STATE_TOWER0,
    Z64_CAMERA_STATE_PARALLEL0,
    Z64_CAMERA_STATE_NORMALD,
    Z64_CAMERA_STATE_SUBJECTD,
    Z64_CAMERA_STATE_START0,
    Z64_CAMERA_STATE_START2,
    Z64_CAMERA_STATE_STOP0,
    Z64_CAMERA_STATE_JCRUISING,
    Z64_CAMERA_STATE_CLIMEMAZE,
    Z64_CAMERA_STATE_SIDED,
    Z64_CAMERA_STATE_DUNGEON2,
    Z64_CAMERA_STATE_BOSS_SHIGE,
    Z64_CAMERA_STATE_KEEPBACK,
    Z64_CAMERA_STATE_CIRCLE6,
    Z64_CAMERA_STATE_CIRCLE7,
    Z64_CAMERA_STATE_CHUBOSS,
    Z64_CAMERA_STATE_RFIXED1,
    Z64_CAMERA_STATE_TRESURE1,
    Z64_CAMERA_STATE_BOMBBASKET,
    Z64_CAMERA_STATE_CIRCLE8,
    Z64_CAMERA_STATE_FUKAN1,
    Z64_CAMERA_STATE_DUNGEON3,
    Z64_CAMERA_STATE_TELESCOPE,
    Z64_CAMERA_STATE_ROOM0,
    Z64_CAMERA_STATE_RCIRC0,
    Z64_CAMERA_STATE_CIRCLE9,
    Z64_CAMERA_STATE_ONTHEPOLE,
    Z64_CAMERA_STATE_INBUSH,
    Z64_CAMERA_STATE_BOSS_LAST,
    Z64_CAMERA_STATE_BOSS_INI,
    Z64_CAMERA_STATE_BOSS_HAK,
    Z64_CAMERA_STATE_BOSS_KON,
    Z64_CAMERA_STATE_CONNECT0,
    Z64_CAMERA_STATE_MORAY,
    Z64_CAMERA_STATE_NORMAL2,
    Z64_CAMERA_STATE_BOMBBOWL,
    Z64_CAMERA_STATE_CIRCLEa,
    Z64_CAMERA_STATE_WHIRLPOOL,
    Z64_CAMERA_STATE_KOKKOGAME,
    Z64_CAMERA_STATE_GIANT,
    Z64_CAMERA_STATE_SCENE0,
    Z64_CAMERA_STATE_ROOM1,
    Z64_CAMERA_STATE_WATER2,
    Z64_CAMERA_STATE_SOKONASI,
    Z64_CAMERA_STATE_FORCEKEEP,
    Z64_CAMERA_STATE_PARALLEL1,
    Z64_CAMERA_STATE_START1,
    Z64_CAMERA_STATE_ROOM2,
    Z64_CAMERA_STATE_NORMAL4,
    Z64_CAMERA_STATE_SHELL,
    Z64_CAMERA_STATE_DUNGEON4,
} z64_camera_state;

// Source: https://wiki.cloudmodding.com/mm/Notes:Mini-Cutscenes#MM_.28J.29_addresses:_Camera_assembly_stuff
typedef enum {
    Z64_CAMERA_MODE_NORMAL,
    Z64_CAMERA_MODE_JUMP,
    Z64_CAMERA_MODE_GORONDASH,
    Z64_CAMERA_MODE_NUTSSHOT,
    Z64_CAMERA_MODE_BOWARROWZ,
    Z64_CAMERA_MODE_NUTSFLY,
    Z64_CAMERA_MODE_SUBJECT,
    Z64_CAMERA_MODE_BOOKEEPON,
    Z64_CAMERA_MODE_ZORAFIN,
    Z64_CAMERA_MODE_KEEPON,
    Z64_CAMERA_MODE_PARALLEL,
    Z64_CAMERA_MODE_TALK,
    Z64_CAMERA_MODE_PACHINCO,
    Z64_CAMERA_MODE_BOWARROW,
    Z64_CAMERA_MODE_BATTLE,
    Z64_CAMERA_MODE_NUTSHIDE,
    Z64_CAMERA_MODE_STILL,
    Z64_CAMERA_MODE_CHARGE,
    Z64_CAMERA_MODE_CLIMB,
    Z64_CAMERA_MODE_CLIMBZ,
    Z64_CAMERA_MODE_FOOKSHOT,
    Z64_CAMERA_MODE_FREEFALL,
    Z64_CAMERA_MODE_HANG,
    Z64_CAMERA_MODE_HANGZ,
    Z64_CAMERA_MODE_PUSHPULL,
    Z64_CAMERA_MODE_NUTSFLYZ,
    Z64_CAMERA_MODE_GORONJUMP,
    Z64_CAMERA_MODE_BOOMERANG,
    Z64_CAMERA_MODE_CHARGEZ,
    Z64_CAMERA_MODE_ZORAFINZ,
} z64_camera_mode;

typedef enum {
    // No timer.
    Z64_TIMER_STATE_NONE,
    // Timer is not being displayed yet.
    Z64_TIMER_STATE_PRE,
    // Timer is in middle of screen.
    Z64_TIMER_STATE_INIT,
    // Timer is moving into position.
    Z64_TIMER_STATE_MOVING,
    // Timer is positioned.
    Z64_TIMER_STATE_SET,
    // Timer is finished and no longer displaying.
    Z64_TIMER_STATE_FINISHED,
} z64_timer_state_t;

/* Macro for checking if a timer state is visible. */
#define IS_TIMER_VISIBLE(TSTATE) (Z64_TIMER_STATE_INIT <= (TSTATE) && (TSTATE) < Z64_TIMER_STATE_FINISHED)

typedef enum {
    // Skull kid on clock tower.
    Z64_TIMER_TYPE_SKULL_KID = 3,
    // Treasure chest game, maybe others.
    Z64_TIMER_TYPE_TCG = 4,
    // Drowning.
    Z64_TIMER_TYPE_DROWNING = 5,
    // None.
    Z64_TIMER_TYPE_NONE = 0x63,
} z64_timer_type_t;

typedef struct
{
  int16_t x;                               // 0x0000
  int16_t y;                               // 0x0002
  int16_t z;                               // 0x0004
} z64_xyz_t;                               // 0x0006

typedef struct
{
  float x;                                 // 0x0000
  float y;                                 // 0x0004
  float z;                                 // 0x0008
} z64_xyzf_t;                              // 0x000C

typedef uint16_t z64_angle_t;
typedef struct
{
  z64_angle_t x;                           // 0x0000
  z64_angle_t y;                           // 0x0002
  z64_angle_t z;                           // 0x0004
} z64_rot_t;                               // 0x0006

typedef union
{
  struct
  {
    uint16_t  a  : 1;
    uint16_t  b  : 1;
    uint16_t  z  : 1;
    uint16_t  s  : 1;
    uint16_t  du : 1;
    uint16_t  dd : 1;
    uint16_t  dl : 1;
    uint16_t  dr : 1;
    uint16_t     : 2;
    uint16_t  l  : 1;
    uint16_t  r  : 1;
    uint16_t  cu : 1;
    uint16_t  cd : 1;
    uint16_t  cl : 1;
    uint16_t  cr : 1;
  };
  uint16_t    pad;                         // 0x0000
} pad_t;                                   // 0x0002

typedef struct
{
  pad_t         pad;                       // 0x0000
  int8_t        x;                         // 0x0002
  int8_t        y;                         // 0x0003
} z64_controller_t;                        // 0x0004

typedef struct
{
  z64_controller_t  raw;                   // 0x0000
  uint16_t          unk_00_;               // 0x0004
  z64_controller_t  raw_prev;              // 0x0006
  uint16_t          unk_01_;               // 0x000A
  pad_t             pad_pressed;           // 0x000C
  int8_t            x_diff;                // 0x000E
  int8_t            y_diff;                // 0x000F
  char              unk_02_[0x0002];       // 0x0010
  pad_t             pad_released;          // 0x0012
  int8_t            adjusted_x;            // 0x0014
  int8_t            adjusted_y;            // 0x0015
  char              unk_03_[0x0002];       // 0x0016
} z64_input_t;                             // 0x0018

typedef struct
{
    uint32_t        size;                  // 0x0000
    Gfx            *buf;                   // 0x0004
    Gfx            *p;                     // 0x0008
    Gfx            *d;                     // 0x000C
} z64_disp_buf_t;

// Partially copying struct from OoT, but tweaked (most fields not verified)
typedef struct
{
    Gfx            *poly_opa_w;            // 0x0000
    Gfx            *poly_xlu_w;            // 0x0004
    char            unk_08_[0x0008];       // 0x0008
    Gfx            *overlay_w;             // 0x0010
    char            unk_14_[0x00A4];       // 0x0014
    Gfx            *work_c;                // 0x00B8
    uint32_t        work_c_size;           // 0x00BC
    char            unk_C0_[0x00F0];       // 0x00C0
    Gfx            *work_w;                // 0x01B0
    z64_disp_buf_t  work;                  // 0x01B4
    char            unk_1C4_[0x00D4];      // 0x01C4, 0x10 bytes less than OoT?
    z64_disp_buf_t  overlay;               // 0x0298
    z64_disp_buf_t  poly_opa;              // 0x02A8
    z64_disp_buf_t  poly_xlu;              // 0x02B8
    uint32_t        frame_count_1;         // 0x02C8
    void           *frame_buffer;          // 0x02CC
    char            unk_2D0_[0x0008];      // 0x02D0
    uint32_t        frame_count_2;         // 0x02D8
    // void           *func_ptr;           // 0x02DC
    // z64_ctxt_t     *ctxt;               // 0x02E0
} z64_gfx_t;

typedef struct
{
    uint8_t unk_00_[0x7C];                 // 0x0000
    void *ctxt;                            // 0x007C
    void *link;                            // 0x0080
    uint8_t unk_84_[0xBC];                 // 0x0084
    int16_t unk_140_;                      // 0x0140
    int16_t state;                         // 0x0142
    int16_t mode;                          // 0x0144
    int16_t unk_146_;                      // 0x0146
    int16_t unk_148_;                      // 0x0148
    int16_t unk_14A_;                      // 0x014A
    int16_t flag_14C;                      // 0x014C
    uint8_t unk_14E_[0x2A];                // 0x014E
} z64_camera_t;                            // 0x0178

typedef struct
{
    z64_gfx_t      *gfx;                   // 0x0000
    void           *state_main;            // 0x0004
    void           *state_dtor;            // 0x0008
    void           *next_ctor;             // 0x000C
    uint32_t        next_size;             // 0x0010
    z64_input_t     input[4];              // 0x0014
    uint32_t        state_heap_size;       // 0x0074
    void           *state_heap;            // 0x0078
    void           *heap_start;            // 0x007C
    void           *heap_end;              // 0x0080
    void           *state_heap_node;       // 0x0084
    char            unk_00_[0x0010];       // 0x0088
    int32_t         state_continue;        // 0x0098
    int32_t         state_frames;          // 0x009C
    uint32_t        unk_01_;               // 0x00A0
                                           // 0x00A4
} z64_ctxt_t;

typedef struct
{
    uint8_t  unk_0_[0x226];                // 0x0000
    uint16_t heartbeat_timer;              // 0x0226
    uint16_t heartbeat_mode;               // 0x0228
    z64_color_rgb16_t heartbeat_inner_rgb; // 0x022A
    z64_color_rgb16_t heartbeat_outer_rgb; // 0x0230
    z64_color_rgb16_2_t heart_inner_rgb;   // 0x0236
    z64_color_rgb16_2_t heart_outer_rgb;   // 0x0242
    uint8_t  unk_24E_[0x18];               // 0x024E
    uint16_t a_button_alpha;               // 0x0266
    uint16_t b_button_alpha;               // 0x0268
    uint16_t c_left_button_alpha;          // 0x026A
    uint16_t c_down_button_alpha;          // 0x026C
    uint16_t c_right_button_alpha;         // 0x026E
    uint16_t hearts_alpha;                 // 0x0270
    uint16_t rupees_alpha;                 // 0x0272, also magic meter alpha
    uint16_t minimap_alpha;                // 0x0274
} z64_game_sub_169E8;

typedef struct
{
    uint8_t unk_0_[0x875];                 // 0x0000
    uint8_t flag_875;                      // 0x0875
    uint8_t unk_876_[0x2D4];               // 0x0876
    uint8_t flag_B4A;                      // 0x0B4A
} z64_game_sub_18000;

typedef struct
{
    z64_ctxt_t         common;             // 0x00000
    uint16_t           scene_number;       // 0x000A4
    uint8_t            scene_code_index;   // 0x000A6
    uint8_t            unk_A7_[0x179];     // 0x000A7
    z64_camera_t       cameras[4];         // 0x00220
    uint8_t            unk_800_[0x14A0];   // 0x00800
    uint8_t            unk_1CA0_;          // 0x01CA0
    uint8_t            unk_1CA1_[0x14D47]; // 0x01CA1
    z64_game_sub_169E8 sub_169E8;          // 0x169E8
    uint8_t            unk_16C5E_[0x13A2]; // 0x16C5E
    z64_game_sub_18000 sub_18000;          // 0x18000
} z64_game_t;

// Note: Currently comparing two separate sources:
//
// - https://wiki.cloudmodding.com/mm/Notes/Deathbasket - N64 version, see "current file stuff"
// - https://www.zeldacodes.org/addresses/mm-u - Likely VC version
//
// Deathbasket's base address is likely what we want: 0x801EF670 (corresponding VC addr is *probably* 0x8110C750)
// Both sets of notes seem to fill in some blanks for each other.
typedef struct
{
    uint32_t entrance;           // 0x0000
    uint8_t unk_04_;             // 0x0004, tatl hint type?
    uint8_t unk_05_;             // 0x0005
    uint8_t unk_06_[4];          // 0x0006
    uint16_t cutscene_flag;      // 0x000A, 0xFFFD if in cutscene?
    uint16_t time_tick;          // 0x000C
    uint8_t unk_0E_[6];          // 0x000E
    uint32_t time_speed;         // 0x0014
    uint16_t time;               // 0x0018
    uint8_t unk_1A_[6];          // 0x001A
    uint8_t form;                // 0x0020
    uint8_t unk_21_;             // 0x0021
    uint8_t tatl_flag;           // 0x0022
    uint8_t save_type;           // 0x0023
    uint8_t zelda3[8];           // 0x0024, "ZELDA3\0\0"
    uint8_t filename[8];         // 0x002C
    uint16_t hearts;             // 0x0034
    uint16_t health;             // 0x0036
    uint8_t has_magic;           // 0x0038, some sort of "has magic" flag
    uint8_t magic;               // 0x0039, current magic amount
    uint16_t rupees;             // 0x003A
    uint32_t playtime;           // 0x003C, play-time frame counter
    uint8_t reset_magic;         // 0x0040
    uint8_t unk_41_;             // 0x0041
    uint8_t double_defense;      // 0x0042
    uint8_t unk_43_[3];          // 0x0043
    union {
        uint16_t owl_statues;    // 0x0046
        struct {
            uint16_t great_bay        : 1;
            uint16_t zora_cape        : 1;
            uint16_t snowhead         : 1;
            uint16_t mountain_village : 1;
            uint16_t clock_town       : 1;
            uint16_t milk_road        : 1;
            uint16_t woodfall         : 1;
            uint16_t southern_swamp   : 1;
            uint16_t ikana_canyon     : 1;
            uint16_t stone_tower      : 1;
            uint16_t                  : 5;
            uint16_t west_clock_town  : 1;
        };
    };
    uint8_t unk_48_[4];          // 0x0048
    uint8_t b_button;            // 0x004C
    uint8_t c_buttons[3];        // 0x004D
    uint8_t goron_b_button;      // 0x0050
    uint8_t unk_51_[3];          // 0x0051
    uint8_t zora_b_button;       // 0x0054
    uint8_t unk_55_[3];          // 0x0055
    uint8_t deku_b_button;       // 0x0058
    uint8_t unk_59_[4];          // 0x0059
    uint8_t alt_c_buttons[3];    // 0x005D
    uint8_t unk_60_[0xD];        // 0x0060
    union {
        uint8_t flag_6D;         // 0x006D
        struct {
            uint8_t sword  : 4;
            uint8_t shield : 4;
        };
    };
    uint8_t unk_6E_[2];          // 0x006E
    union {
        uint8_t inventory[0x30]; // 0x0070
        struct {
            uint8_t items[0x18]; // 0x0070
            uint8_t masks[0x18]; // 0x0088
        };
    };
    uint8_t item_count[0x18];    // 0x00A0
    uint8_t unk_B8_[2];          // 0x00B8
    union {
        uint8_t flag_BA;         // 0x00BA
        struct {
            uint8_t        : 2;
            uint8_t wallet : 2;  // 0 = child, 1 = adult, 2 = giant
            uint8_t        : 4;
        };
    };
    union {
        uint8_t flag_BB;         // 0x00BB
        struct {
            uint8_t quiver   : 3;
            uint8_t bomb_bag : 2;
            uint8_t          : 3;
        };
    };
    union {
        uint8_t flag_BC;         // 0x00BC
        struct {
            uint8_t lullaby_intro : 4;
            uint8_t heart_pieces  : 4;
        };
    };
    union {
        uint8_t flag_BD;         // 0x00BD
        struct {
            uint8_t song_of_storms   : 1;
            uint8_t                  : 1;
            uint8_t bombers_notebook : 1;
            uint8_t                  : 5;
        };
    };
    union {
        uint8_t flag_BE;         // 0x00BE
        struct {
            uint8_t new_wave_bossa_nova : 1;
            uint8_t elegy_of_emptiness  : 1;
            uint8_t oath_to_order       : 1;
            uint8_t                     : 1;
            uint8_t song_of_time        : 1;
            uint8_t song_of_healing     : 1;
            uint8_t eponas_song         : 1;
            uint8_t song_of_soaring     : 1;
        };
    };
    union {
        uint8_t flag_BF;         // 0x00BF
        struct {
            uint8_t odolwa_remains      : 1;
            uint8_t goht_remains        : 1;
            uint8_t gyorg_remains       : 1;
            uint8_t twinmold_remains    : 1;
            uint8_t                     : 2;
            uint8_t sonata_of_awakening : 1;
            uint8_t goron_lullaby       : 1;
        };
    };
    uint8_t unk_C0_[0xA];        // 0x00C0
    uint8_t small_keys[4];       // 0x00CA
    uint8_t unk_CE_[5];          // 0x00CE
    uint8_t doubled_hearts;      // 0x00D3
    uint8_t unk_D4_[0xE0A];      // 0x00D4
    uint16_t bank_rupees;        // 0x0EDE
    uint8_t unk_EE0_[0x10];      // 0x0EE0
    uint32_t lottery_guess;      // 0x0EF0
    uint8_t unk_EF4_[0x12];      // 0x0EF4
    union {
        uint8_t flag_F06;        // 0x0F06
        struct {
            uint8_t                : 4;
            uint8_t infinite_magic : 1;
            uint8_t                : 3;
        };
    };
    uint8_t unk_F07_[0x8];       // 0x0F07
    uint8_t great_spin;          // 0x0F0F
    uint8_t unk_F10[0x4C];       // 0x0F10
    uint32_t locations_visited;  // 0x0F5C
    uint8_t unk_F60[0x7C];       // 0x0F60
    uint8_t lotteries[9];        // 0x0FDC
    uint8_t unk_FE5_[6];         // 0x0FE5
    uint8_t bomber_code[5];      // 0x0FEB
    uint8_t unk_FF0_[0x26];      // 0x0FF0
    uint16_t jinx_timer;         // 0x1016
    int16_t rupee_timer;         // 0x1018
    uint8_t unk_101A_[0x2DB6];   // 0x101A
    uint8_t timer_state[0x40];   // 0x3DD0
    uint8_t unk_3E10_[0x108];    // 0x3E10‬
    uint8_t b_button_usable;     // 0x3F18
    uint8_t c_buttons_usable[3]; // 0x3F19
    uint8_t a_button_usable;     // 0x3F1C
    uint8_t unk_3F1D_[3];        // 0x3F1D
    uint16_t pre_game_state;     // 0x3F20, game state in relation to alpha transition?
    uint16_t game_state;         // 0x3F22
    uint16_t alpha_transition;   // 0x3F24
    uint16_t sub_game_state;     // 0x3F26, might be "previous" game state but not sure
    uint8_t unk_3F28_[0x6];      // 0x3F28
    uint16_t magic_meter_size;   // 0x3F2E
    uint8_t unk_3F30_[0x19A8];   // 0x3F30
    z64_color_rgb16_t heart_dd_beating_rgb; // 0x58D8
    uint8_t unk_58DE_[0x12];                // 0x58DE
    z64_color_rgb16_t heart_dd_rgb;         // 0x58F0
} z64_file_t;

typedef struct
{
    struct
    {
        uint8_t damage : 4;
        uint8_t effect : 4;
    } attack[0x20];
} z64_actor_damage_table_t;

typedef struct z64_actor_s z64_actor_t;

/* actor callback prototypes */
typedef void (*z64_ActorMain_proc)(z64_actor_t *actor, z64_game_t *game);
typedef void (*z64_ActorDraw_proc)(z64_actor_t *actor, z64_game_t *game);

// Source: https://wiki.cloudmodding.com/mm/Actors
struct z64_actor_s
{
    uint16_t                 id;                     // 0x0000, Actor Id.
    uint8_t                  type;                   // 0x0002, Actor Type. See Below
    uint8_t                  room;                   // 0x0003, Room number the actor is part of. FF denotes that the actor won't despawn on a room change
    int32_t                  flags;                  // 0x0004, flags used for drawing stuff?
                                                     // & 0x0040 0000 = Affects actor lighting
                                                     // & 0x0000 1000 = ?
                                                     // & 0x0000 0040 = ?
    z64_xyzf_t                pos1;                  // 0x0008, Related to collision detection routine
    z64_rot_t                 init_rot;              // 0x0014, Initial Rotation when spawned
    uint16_t                  unk_1A_;               // 0x001A
    uint16_t                  variable;              // 0x001C, Configurable variable set by an actor's spawn data
    int8_t                    obj_table_index;       // 0x001E, index to table at Global Context + ????
    uint8_t                   unk_1F_;               // 0x001F
    uint16_t                  sound_effect;          // 0x0020, Plays sound effect relative to actor's location (if within range of camera?)
    uint16_t                  unk_22_;               // 0x0022
    z64_xyzf_t                position;              // 0x0024, Current coordinates
    z64_rot_t                 speed_rot;             // 0x0030, 0x32 sets what direction the 0x68 speedXZ variable is moving the actor
    uint16_t                  unk_36_;               // 0x0036, same as 0x1A
    int8_t                    unk_38_;               // 0x0038
    uint8_t                   unk_39_;               // 0x0039
    uint16_t                  unk_3A_;               // 0x003A
    z64_xyzf_t                pos3;                  // 0x003C, Related to camera
    z64_rot_t                 rot1;                  // 0x0048, 0x30 rotation copied into here
    uint16_t                  unk_4E_;               // 0x004E
    int32_t                   unk_50_;               // 0x0050
    float                     unk_54_;               // 0x0054, I know this is a float from breakpointing it
    z64_xyzf_t                scale;                 // 0x0058, sets x,y,z scaling factor. Typically, a factor of 0.01 is used for each axis
    z64_xyzf_t                velocity;              // 0x0064
    float                     speedXZ;               // 0x0070, Always positive, stores how fast the actor is traveling along the XZ plane
    float                     gravity;               // 0x0074, acceleration due to gravity; value is added to Y velocity every frame
    float                     min_velocity_y;        // 0x0078, sets the lower bounds cap on velocity along the Y axis struct, collision related
    int*                      wall_poly;             // 0x007C, Wall polygon an actor is touching
    int*                      floor_poly;            // 0x0080, Floor polygon an actor is over/touching
    uint8_t                   wall_poly_src;         // 0x0084, Complex Poly Surface Source. 0x32 = Scene
    uint8_t                   floor_poly_src;        // 0x0085, Complex Poly Surface Source. 0x32 = Scene
    uint16_t                  wallrot;               // 0x0086
    float                     unk_88_;               // 0x0088, floor poly height?
    float                     water_surface_dist;    // 0x008C
    uint16_t                  bgcheck_flags;         // 0x0090, unknown
    int16_t                   unk_roty;              // 0x0092, rotation y (give item, possibly next facing dir?/face toward link?)
    float                     _unk_94;               // 0x0094
    float                     xz_distance_from_link; // 0x0098
    float                     y_distance_from_link;  // 0x009C, relative distance

    // 8-10-2012 : Addition made by Jason777
    // For actors which contain a damage chart (example: Stalfos)...
    z64_actor_damage_table_t* damage_table;          // 0x00A0, Pointer to the actor's Damage Chart in RAM.
    z64_xyzf_t                displacement;          // 0x00A4, amount to correct velocity (0x5C) by when colliding into a body
    int16_t                   unk_B0_;               // 0x00B0
    int16_t                   unk_B2_;               // 0x00B2
    uint16_t                  unk_B4_;               // 0x00B4
    uint8_t                   mass;                  // 0x00B6, Used to compute displacement, 50 is common value, 0xFF for infinite mass/unmoveable
    uint8_t                   health;                // 0x00B7
    uint8_t                   damage;                // 0x00B8
    uint8_t                   damage_effect;         // 0x00B9, Stores what effect should occur when hit by a weapon
    uint8_t                   impact_effect;         // 0x00BA
    uint8_t                   unk_BB_;               // 0x00BB

    z64_rot_t                 rot_2;                 // 0x00BC, Setting this immediately changes actor's rotation
    uint8_t                   unk_C2_[0x53];         // 0x00C2
    uint8_t                   run_actor;             // 0x0115, Determines if actor instance should be processed. 01 for yes, 00 for no.
    uint8_t                   unk_116_[0x12];        // 0x0116
    z64_actor_t*              actor_prev;            // 0x0128, Previous z_ram_actor of this type
    z64_actor_t*              actor_next;            // 0x012C, Next z_ram_actor of this type
    void*                     Init;                  // 0x0130, Actor Constructor?
    void*                     Dest;                  // 0x0134, Actor Deconstructor?
    z64_ActorMain_proc        Main;                  // 0x0138
    z64_ActorDraw_proc        Draw;                  // 0x013C
    void*                     CodeEntry;             // 0x0140, Address to source overlay file's reference in code (file)
    // ?
    // From here on, the structure and size varies for each actor
};

typedef struct {
    z64_actor_t common;         // 0x0000
    uint8_t unk_144_[0x116];    // 0x0144
    uint16_t anim_timer;        // 0x025A, counts from 0 to 0x5F as "fairy heal" animation progresses
} z64_fairy_actor_t;

typedef struct {
    z64_actor_t common;         // 0x0000
    uint8_t unk_144_[2];        // 0x0144
    uint8_t pre_use;            // 0x0146
    uint8_t unk_147_[3];        // 0x0147
    uint8_t item_out;           // 0x014A, which item Link currently has out?
                                // 0x14 = Ocarina, 0x15 = Bottle, 0x9 = Bow, 0xD = Hookshot
    uint8_t form;               // 0x014B
    uint8_t unk_14C_[7];        // 0x014C
    uint8_t mask;               // 0x0153
    uint8_t mask_c;             // 0x0154, C button index (starting at 1) of current/recently worn mask
    uint8_t previous_mask;      // 0x0155
    uint8_t unk_156_[0x916];    // 0x0156
    uint32_t action_state1;     // 0x0A6C
    uint32_t action_state2;     // 0x0A70
    uint32_t action_state3;     // 0x0A74
    uint8_t unk_A78_[0x6F];     // 0x0A78
    uint8_t anim_timer;         // 0x0AE7, some animation timer? Relevant to: transformation masks, freezing, etc
    uint16_t frozen_timer;      // 0x0AE8
    uint8_t unk_AEA_[0x88];     // 0x0AEA
    uint16_t floor_type;        // 0x0B72, determines sound effect used while walking
} z64_link_t;

typedef struct {
    void               *ram;                    /* 0x0000 */
    uint32_t            vrom_start;             /* 0x0004 */
    uint32_t            vrom_end;               /* 0x0008 */
    uint32_t            vram_start;             /* 0x000C */
    uint32_t            vram_end;               /* 0x0010 */
    char                unk_0x14[4];            /* 0x0014 */
    char               *filename;               /* 0x0018 */
} z64_player_ovl_table_t;                       /* 0x001C */

typedef struct
{
    int16_t     unk_00_;        // 0x0000
    int16_t     unk_02_;        // 0x0002
    int16_t     unk_04_;        // 0x0004
    int16_t     unk_06_;        // 0x0006
    uint32_t    unk_08_;        // 0x0008
    uint32_t    unk_0C_;        // 0x000C
    z64_game_t *game;           // 0x0010
    int16_t     unk_14_;        // 0x0014
    int16_t     unk_16_;        // 0x0016
} z64_0x801BD8B0_t;

typedef struct {
    z64_player_ovl_table_t  pause_ovl;          /* 0x0000, VRAM: [0x808160A0, 0x8082DA90) */
    z64_player_ovl_table_t  player_ovl;         /* 0x001C, VRAM: [0x8082DA90, 0x80862B70) */
    void                   *start;              /* 0x0038, RAM start address to use. */
    z64_player_ovl_table_t *selected;           /* 0x003C, points to selected overlay. */
} z64_0x801D0B70_t;                             /* 0x0040 */

typedef struct {
    union {
        uint16_t digits[8];                     /* 0x0000 */
        struct {
            uint16_t minutes[2];                /* 0x0000 */
            uint16_t colon1;                    /* 0x0004 */
            uint16_t seconds[2];                /* 0x0006 */
            uint16_t colon2;                    /* 0x000A */
            uint16_t milliseconds[2];           /* 0x000C */
            uint16_t beep_seconds;              /* 0x0010, previous seconds[1] value that had a beep. */
                                                /*         Likely used to determine when to do the next beep. */
        };
    };
} z64_timer_digits_t;                           /* 0x0012 */

// virtual file addresses
#define z64_item_texture_file             0xA36C10

// dram addresses
#define z64_file_addr                     0x801EF670
#define z64_ctxt_addr                     0x803E6B20
#define z64_game_addr                     z64_ctxt_addr
#define z64_link_addr                     0x803FFDB0

// data
#define z64_ctxt                          (*(z64_ctxt_t*) z64_ctxt_addr)
#define z64_file                          (*(z64_file_t*) z64_file_addr)
#define z64_game                          (*(z64_game_t*) z64_game_addr)
#define z64_link                          (*(z64_link_t*) z64_link_addr)

// data (unknown)
#define z64_0x801BD8B0                    (*(z64_0x801BD8B0_t*) 0x801BD8B0)
#define z64_0x801D0B70                    (*(z64_0x801D0B70_t*) 0x801D0B70)

// dram function addresses
#define z64_CanInteract_addr              0x801233E4
#define z64_CanInteract2_addr             0x80123358
#define z64_DrawButtonAmounts_addr        0x80117BD0
#define z64_DrawBButtonIcon_addr          0x80118084
#define z64_DrawCButtonIcons_addr         0x80118890
#define z64_GetFloorPhysicsType_addr      0x800C99D4
#define z64_GetPhysicalAddrOfFile_addr    0x80080950
#define z64_LoadItemTexture_addr          0x80178DAC
#define z64_PlaySfx_addr                  0x8019F0C8
#define z64_ReadFile_addr                 0x80080C90
#define z64_SpawnActor_addr               0x800BAC60
#define z64_UpdateButtonUsability_addr    0x80110038
#define z64_WriteHeartColors_addr         0x8010069C

// Relocatable functions
#define z64_LinkDamage_vram               0x80833B18
#define z64_LinkInvincibility_vram        0x80833998
#define z64_UseItem_vram                  0x80831990

// function prototypes
typedef int (*z64_CanInteract_proc)(z64_game_t *game);
typedef int (*z64_CanInteract2_proc)(z64_game_t *game, z64_link_t *link);
typedef void (*z64_DrawButtonAmounts_proc)(z64_game_t *game, uint32_t arg1, uint16_t alpha);
typedef void (*z64_DrawBButtonIcon_proc)(z64_game_t *game);
typedef void (*z64_DrawCButtonIcons_proc)(z64_game_t *game);
typedef uint32_t (*z64_GetFloorPhysicsType_proc)(void *arg0, void *arg1, uint8_t arg2);
typedef uint32_t (*z64_GetPhysicalAddrOfFile_proc)(uint32_t vrom_addr);
typedef void (*z64_LinkDamage_proc)(z64_game_t *game, z64_link_t *link, uint32_t type, uint32_t arg3);
typedef void (*z64_LinkInvincibility_proc)(z64_link_t *link, uint8_t frames);
typedef void (*z64_LoadItemTexture_proc)(uint32_t phys_file, uint8_t item, uint8_t *dest, uint32_t length);
typedef void (*z64_PlaySfx_proc)(uint32_t id);
typedef void (*z64_ReadFile_proc)(void *mem_addr, uint32_t vrom_addr, uint32_t size);
typedef z64_actor_t* (*z64_SpawnActor_proc)(void *unk0, z64_game_t *game, uint16_t id, float x, float y, float z, uint16_t rotx, uint16_t roty, uint16_t rotz, uint32_t inst);
typedef void (*z64_UpdateButtonUsability_proc)(z64_ctxt_t *ctxt);
typedef void (*z64_UseItem_proc)(z64_ctxt_t *ctxt, z64_link_t *link, uint8_t item);
typedef void (*z64_WriteHeartColors_proc)(z64_game_t *game);

// functions
#define z64_CanInteract                   ((z64_CanInteract_proc) z64_CanInteract_addr)
#define z64_CanInteract2                  ((z64_CanInteract2_proc) z64_CanInteract2_addr)
#define z64_DrawButtonAmounts             ((z64_DrawButtonAmounts_proc) z64_DrawButtonAmounts_addr)
#define z64_DrawBButtonIcon               ((z64_DrawBButtonIcon_proc) z64_DrawBButtonIcon_addr)
#define z64_DrawCButtonIcons              ((z64_DrawCButtonIcons_proc) z64_DrawCButtonIcons_addr)
#define z64_GetFloorPhysicsType           ((z64_GetFloorPhysicsType_proc) z64_GetFloorPhysicsType_addr)
#define z64_GetPhysicalAddrOfFile         ((z64_GetPhysicalAddrOfFile_proc) z64_GetPhysicalAddrOfFile_addr)
#define z64_LoadItemTexture               ((z64_LoadItemTexture_proc) z64_LoadItemTexture_addr)
#define z64_PlaySfx                       ((z64_PlaySfx_proc) z64_PlaySfx_addr)
#define z64_ReadFile                      ((z64_ReadFile_proc) z64_ReadFile_addr)
#define z64_SpawnActor                    ((z64_SpawnActor_proc) z64_SpawnActor_addr)
#define z64_UpdateButtonUsability         ((z64_UpdateButtonUsability_proc) z64_UpdateButtonUsability_addr)
#define z64_WriteHeartColors              ((z64_WriteHeartColors_proc) z64_WriteHeartColors_addr)

#endif // Z64_H
