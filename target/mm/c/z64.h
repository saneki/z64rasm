#ifndef Z64_H
#define Z64_H

#include <n64.h>
#include <stdint.h>

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
    Z64_SLOT_FIERCE_DIETY_MASK,
} z64_mask_slot_t;

typedef enum {
    Z64_GAME_STATE_BLACK_SCREEN,
    Z64_GAME_STATE_TRANSITION,
    Z64_GAME_STATE_TRANSITION_2,
    Z64_GAME_STATE_DIALOGUE = 5,
    Z64_GAME_STATE_PAUSE = 7,
    Z64_GAME_STATE_MINIGAME = 0xC,
    Z64_GAME_STATE_ITEM_PROMPT = 0x10,
    Z64_GAME_STATE_NORMAL = 0x32,
} z64_game_state_t;

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
  uint16_t    pad;                        // 0x0000
} pad_t;                                  // 0x0002

typedef struct
{
  pad_t         pad;                      // 0x0000
  int8_t        x;                        // 0x0002
  int8_t        y;                        // 0x0003
} z64_controller_t;                       // 0x0004

typedef struct
{
  z64_controller_t  raw;                  // 0x0000
  uint16_t          unk_00_;              // 0x0004
  z64_controller_t  raw_prev;             // 0x0006
  uint16_t          unk_01_;              // 0x000A
  pad_t             pad_pressed;          // 0x000C
  int8_t            x_diff;               // 0x000E
  int8_t            y_diff;               // 0x000F
  char              unk_02_[0x0002];      // 0x0010
  pad_t             pad_released;         // 0x0012
  int8_t            adjusted_x;           // 0x0014
  int8_t            adjusted_y;           // 0x0015
  char              unk_03_[0x0002];      // 0x0016
} z64_input_t;                            // 0x0018

typedef struct
{
    uint32_t        size;                 /* 0x0000 */
    Gfx            *buf;                  /* 0x0004 */
    Gfx            *p;                    /* 0x0008 */
    Gfx            *d;                    /* 0x000C */
} z64_disp_buf_t;

// Partially copying struct from OoT, but tweaked (most fields not verified)
typedef struct
{
    Gfx            *poly_opa_w;           /* 0x0000 */
    Gfx            *poly_xlu_w;           /* 0x0004 */
    char            unk_00_[0x0008];      /* 0x0008 */
    Gfx            *overlay_w;            /* 0x0010 */
    char            unk_01_[0x00A4];      /* 0x0014 */
    Gfx            *work_c;               /* 0x00B8 */
    uint32_t        work_c_size;          /* 0x00BC */
    char            unk_02_[0x00F0];      /* 0x00C0 */
    Gfx            *work_w;               /* 0x01B0 */
    z64_disp_buf_t  work;                 /* 0x01B4 */
    char            unk_03_[0x00D4];      /* 0x01C4 */ // 0x10 bytes less than OoT?
    z64_disp_buf_t  overlay;              /* 0x0298 */
    z64_disp_buf_t  poly_opa;             /* 0x02A8 */
    z64_disp_buf_t  poly_xlu;             /* 0x02B8 */
    uint32_t        frame_count_1;        /* 0x02C8 */
    void           *frame_buffer;         /* 0x02CC */
    char            unk_04_[0x0008];      /* 0x02D0 */
    uint32_t        frame_count_2;        /* 0x02D8 */
    // void           *func_ptr;          /* 0x02DC */
    // z64_ctxt_t     *ctxt;              /* 0x02E0 */
} z64_gfx_t;

typedef struct
{
    z64_gfx_t      *gfx;                  /* 0x0000 */
    void           *state_main;           /* 0x0004 */
    void           *state_dtor;           /* 0x0008 */
    void           *next_ctor;            /* 0x000C */
    uint32_t        next_size;            /* 0x0010 */
    z64_input_t     input[4];             /* 0x0014 */
    uint32_t        state_heap_size;      /* 0x0074 */
    void           *state_heap;           /* 0x0078 */
    void           *heap_start;           /* 0x007C */
    void           *heap_end;             /* 0x0080 */
    void           *state_heap_node;      /* 0x0084 */
    char            unk_00_[0x0010];      /* 0x0088 */
    int32_t         state_continue;       /* 0x0098 */
    int32_t         state_frames;         /* 0x009C */
    uint32_t        unk_01_;              /* 0x00A0 */
                                          /* 0x00A4 */
} z64_ctxt_t;

// Note: Currently comparing two separate sources:
//
// - https://wiki.cloudmodding.com/mm/Notes/Deathbasket - N64 version, see "current file stuff"
// - https://www.zeldacodes.org/addresses/mm-u - Likely VC version
//
// Deathbasket's base address is likely what we want: 0x801EF670 (corresponding VC addr is *probably* 0x8110C750)
// Both sets of notes seem to fill in some blanks for each other.
typedef struct
{
    uint32_t entrance;      // 0x0000
    uint8_t unk_04_;        // 0x0004, tatl hint type?
    uint8_t unk_05_;        // 0x0005
    uint8_t unk_06_[4];     // 0x0006
    uint16_t cutscene_flag; // 0x000A, 0xFFFD if in cutscene?
    uint16_t time_tick;     // 0x000C
    uint8_t unk_0E_[6];     // 0x000E
    uint32_t time_speed;    // 0x0014
    uint16_t time;          // 0x0018
    uint8_t unk_1A_[6];     // 0x001A
    uint8_t form;           // 0x0020
    uint8_t unk_21_;        // 0x0021
    uint8_t tatl_flag;      // 0x0022
    uint8_t save_type;      // 0x0023
    uint8_t zelda3[8];      // 0x0024, "ZELDA3\0\0"
    uint8_t filename[8];    // 0x002C
    uint16_t hearts;        // 0x0034
    uint16_t health;        // 0x0036
    uint8_t has_magic;      // 0x0038, some sort of "has magic" flag
    uint8_t magic;          // 0x0039, current magic amount
    uint16_t rupees;        // 0x003A
    uint32_t playtime;      // 0x003C, play-time frame counter
    uint8_t unk_40_[2];     // 0x0040
    uint8_t double_defense; // 0x0042
    uint8_t unk_43_[3];     // 0x0043
    union {
        uint16_t owl_statues; // 0x0046
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
    uint8_t unk_48_[4];     // 0x0048
    uint8_t b_button;       // 0x004C
    uint8_t c_buttons[3];   // 0x004D
    uint8_t unk_50_[0xD];   // 0x0050
    uint8_t alt_c_buttons[3]; // 0x005D
    uint8_t unk_60_[0xD];   // 0x0060
    union {
        uint8_t sword_shield_equip; // 0x006D
        struct {
            uint8_t sword_equip  : 4;
            uint8_t shield_equip : 4;
        };
    };
    uint8_t unk_6E_[2];      // 0x006E
    uint8_t items[0x18];     // 0x0070
    uint8_t masks[0x18];     // 0x0088
    uint8_t item_count[0x18];// 0x00A0
    uint8_t unk_B8_[2];      // 0x00B8
    uint8_t wallet;          // 0x00BA
    union {
        uint8_t quiver_bomb_bag; // 0x00BB
        struct {
            uint8_t quiver   : 3;
            uint8_t bomb_bag : 2;
            uint8_t          : 3;
        };
    };
    union {
        uint8_t heart_pieces_lullaby; // 0x00BC
        struct {
            uint8_t lullaby_intro : 4;
            uint8_t heart_pieces  : 4;
        };
    };
    union {
        uint8_t song_of_storms_notebook; // 0x00BD
        struct {
            uint8_t song_of_storms   : 1;
            uint8_t                  : 1;
            uint8_t bombers_notebook : 1;
            uint8_t                  : 5;
        };
    };
    union {
        uint8_t songs; // 0x00BE
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
        uint8_t remains; // 0x00BF
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
    uint8_t unk_C0_[0xA];       // 0x00C0
    uint8_t small_keys[4];      // 0x00CA
    uint8_t unk_CE_[5];         // 0x00CE
    uint8_t doubled_hearts;     // 0x00D3
    uint8_t unk_D4_[0xE0A];     // 0x00D4
    uint16_t bank_rupees;       // 0x0EDE
    uint8_t unk_EE0_[0x2F];     // 0x0EE0
    uint8_t great_spin;         // 0x0F0F
    uint8_t unk_F10[0x4C];      // 0x0F10
    uint32_t locations_visited; // 0x0F5C
    uint8_t unk_F60[0x86];      // 0x0F60
    uint8_t bomber_count;       // 0x0FE6, set to 5 once the bomber code is obtained
    uint8_t bomber_code[5];     // 0x0FE7, cosmetic??
    uint8_t unk_FEC_[0x2F2C];   // 0x0FEC
    uint8_t b_button_usable;     // 0x3F18
    uint8_t c_buttons_usable[3]; // 0x3F19
    uint8_t unk_3F1C_[4];        // 0x3F1C
    uint16_t pre_game_state;     // 0x3F20
    uint16_t game_state;         // 0x3F22
    uint8_t unk_3F24_[0xA];      // 0x3F24
    uint16_t magic_meter_size;   // 0x3F2E
} z64_file_t;

typedef struct {
    /// ...
    uint8_t unk_00_[0x146];     // 0x0000
    uint8_t pre_use;            // 0x0146
} z64_link_t;

/* dram addresses */
#define z64_ReadFile_addr  0x80080C90
#define z64_file_addr      0x801EF670
#define z64_ctxt_addr      0x803E6B20
#define z64_link_addr      0x803FFDB0
#define z64_UpdateButtonUsability_addr 0x80110038
#define z64_UseItem_addr   0x8074EE20

/* data */
#define z64_ctxt           (*(z64_ctxt_t*) z64_ctxt_addr)
#define z64_file           (*(z64_file_t*) z64_file_addr)
#define z64_link           (*(z64_link_t*) z64_link_addr)

/* function prototypes */
typedef void (*z64_ReadFile_proc)(void *mem_addr, uint32_t vrom_addr, uint32_t size);
typedef void (*z64_UpdateButtonUsability_proc)(z64_ctxt_t *ctxt);
typedef void (*z64_UseItem_proc)(z64_ctxt_t *ctxt, z64_link_t *link, uint8_t item);

/* functions */
#define z64_ReadFile       ((z64_ReadFile_proc) z64_ReadFile_addr)
#define z64_UpdateButtonUsability ((z64_UpdateButtonUsability_proc) z64_UpdateButtonUsability_addr)
#define z64_UseItem        ((z64_UseItem_proc) z64_UseItem_addr)

#endif
