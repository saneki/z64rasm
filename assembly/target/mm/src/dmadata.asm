; DMA Table constants
G_BASE equ                "../roms/base.z64"
.definelabel G_DMA_TABLE, 0x1A500

.macro DefineDmaFile, DmaVar, FileVar, Index
    .definelabel DmaVar,  G_DMA_TABLE + (0x10 * Index)
    .definelabel FileVar, (readbyte(G_BASE, (DmaVar + 8)) << 24 | readbyte(G_BASE, (DmaVar + 9)) << 16 | readbyte(G_BASE, (DmaVar + 10)) << 8 | readbyte(G_BASE, (DmaVar + 11)))
.endmacro

DefineDmaFile G_CODE_DMA, G_CODE_FILE, 31
.definelabel  G_CODE_RAM, 0x800A5AC0

; ovl_file_choose
DefineDmaFile G_FILE_CHOOSE_DMA, G_FILE_CHOOSE_FILE, 35
.definelabel  G_FILE_CHOOSE_VRAM, 0x80804010

; ovl_kaleido_scope (Pause menu)
DefineDmaFile G_KALEIDO_SCOPE_DMA, G_KALEIDO_SCOPE_FILE, 37
.definelabel  G_KALEIDO_SCOPE_VRAM, 0x808160A0

; ovl_player_actor
DefineDmaFile G_PLAYER_ACTOR_DMA, G_PLAYER_ACTOR_FILE, 38
.definelabel  G_PLAYER_ACTOR_VRAM, 0x8082DA90

; ovl_Obj_Oshihiki (Pushblock)
DefineDmaFile G_OBJ_OSHIHIKI_DMA, G_OBJ_OSHIHIKI_FILE, 115
.definelabel  G_OBJ_OSHIHIKI_VRAM, 0x80917290

; ovl_Obj_Iceblock
DefineDmaFile G_OBJ_ICEBLOCK_DMA, G_OBJ_ICEBLOCK_FILE, 288
.definelabel  G_OBJ_ICEBLOCK_VRAM, 0x80A23090

; ovl_Bg_Dblue_Movebg (Great Bay Temple faucets)
DefineDmaFile G_BG_DBLUE_MOVEBG_DMA, G_BG_DBLUE_MOVEBG_FILE, 290
.definelabel  G_BG_DBLUE_MOVEBG_VRAM, 0x80A29A80

; ovl_En_Si (Skulltula Token)
DefineDmaFile G_EN_SI_DMA, G_EN_SI_FILE, 315
.definelabel  G_EN_SI_VRAM, 0x80A45360

; ovl_En_Time_Tag
DefineDmaFile G_EN_TIME_TAG_DMA, G_EN_TIME_TAG_FILE, 392
.definelabel  G_EN_TIME_TAG_VRAM, 0x80AC9EA0

; ovl_En_Elforg (Stray Fairy)
DefineDmaFile G_EN_ELFORG_DMA, G_EN_ELFORG_FILE, 397
.definelabel  G_EN_ELFORG_VRAM, 0x80ACC470
