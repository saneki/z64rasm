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
DefineDmaFile G_FILESELECT_DMA, G_FILESELECT_FILE, 35
.definelabel  G_FILESELECT_VRAM, 0x80804010

; ovl_kaleido_scope
DefineDmaFile G_KALEIDO_DMA, G_KALEIDO_FILE, 37
.definelabel  G_KALEIDO_VRAM, 0x808160A0

; ovl_player_actor
DefineDmaFile G_PLAYER_DMA, G_PLAYER_FILE, 38
.definelabel  G_PLAYER_VRAM, 0x8082DA90

; ovl_Obj_Oshihiki
DefineDmaFile G_PUSHBLOCK_DMA, G_PUSHBLOCK_FILE, 115
.definelabel  G_PUSHBLOCK_VRAM, 0x80917290

; ovl_Obj_Iceblock
DefineDmaFile G_ICEBLOCK_DMA, G_ICEBLOCK_FILE, 288
.definelabel  G_ICEBLOCK_VRAM, 0x80A23090

; ovl_Bg_Dblue_Movebg
DefineDmaFile G_FAUCET_DMA, G_FAUCET_FILE, 290
.definelabel  G_FAUCET_VRAM, 0x80A29A80

; ovl_En_Time_Tag
DefineDmaFile G_EN_TIME_TAG_DMA, G_EN_TIME_TAG_FILE, 392
.definelabel  G_EN_TIME_TAG_VRAM, 0x80AC9EA0
