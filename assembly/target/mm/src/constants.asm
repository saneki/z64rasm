; DMA Table constants
G_BASE equ                    "../roms/base.z64"
.definelabel G_DMA_TABLE,     0x1A500

.definelabel G_CODE_DMA,      G_DMA_TABLE + (0x10 * 31)
.definelabel G_CODE_FILE,     (readbyte(G_BASE, (G_CODE_DMA + 8)) << 24 | readbyte(G_BASE, (G_CODE_DMA + 9)) << 16 | readbyte(G_BASE, (G_CODE_DMA + 10)) << 8 | readbyte(G_BASE, (G_CODE_DMA + 11)))
.definelabel G_CODE_RAM,      0x800A5AC0

; ovl_file_choose
.definelabel G_FILESELECT_DMA,  G_DMA_TABLE + (0x10 * 35)
.definelabel G_FILESELECT_FILE, (readbyte(G_BASE, (G_FILESELECT_DMA + 8)) << 24 | readbyte(G_BASE, (G_FILESELECT_DMA + 9)) << 16 | readbyte(G_BASE, (G_FILESELECT_DMA + 10)) << 8 | readbyte(G_BASE, (G_FILESELECT_DMA + 11)))

; ovl_kaleido_scope
.definelabel G_KALEIDO_DMA,     G_DMA_TABLE + (0x10 * 37)
.definelabel G_KALEIDO_FILE,    (readbyte(G_BASE, (G_KALEIDO_DMA + 8)) << 24 | readbyte(G_BASE, (G_KALEIDO_DMA + 9)) << 16 | readbyte(G_BASE, (G_KALEIDO_DMA + 10)) << 8 | readbyte(G_BASE, (G_KALEIDO_DMA + 11)))

; ovl_player_actor
.definelabel G_PLAYER_DMA,      G_DMA_TABLE + (0x10 * 38)
.definelabel G_PLAYER_FILE,     (readbyte(G_BASE, (G_PLAYER_DMA + 8)) << 24 | readbyte(G_BASE, (G_PLAYER_DMA + 9)) << 16 | readbyte(G_BASE, (G_PLAYER_DMA + 10)) << 8 | readbyte(G_BASE, (G_PLAYER_DMA + 11)))

; ovl_Obj_Oshihiki
.definelabel G_PUSHBLOCK_DMA,   G_DMA_TABLE + (0x10 * 115)
.definelabel G_PUSHBLOCK_FILE,  (readbyte(G_BASE, (G_PUSHBLOCK_DMA + 8)) << 24 | readbyte(G_BASE, (G_PUSHBLOCK_DMA + 9)) << 16 | readbyte(G_BASE, (G_PUSHBLOCK_DMA + 10)) << 8 | readbyte(G_BASE, (G_PUSHBLOCK_DMA + 11)))

; ovl_Obj_Iceblock
.definelabel G_ICEBLOCK_DMA,    G_DMA_TABLE + (0x10 * 288)
.definelabel G_ICEBLOCK_FILE,   (readbyte(G_BASE, (G_ICEBLOCK_DMA + 8)) << 24 | readbyte(G_BASE, (G_ICEBLOCK_DMA + 9)) << 16 | readbyte(G_BASE, (G_ICEBLOCK_DMA + 10)) << 8 | readbyte(G_BASE, (G_ICEBLOCK_DMA + 11)))

; ovl_Bg_Dblue_Movebg
.definelabel G_FAUCET_DMA,      G_DMA_TABLE + (0x10 * 290)
.definelabel G_FAUCET_FILE,     (readbyte(G_BASE, (G_FAUCET_DMA + 8)) << 24 | readbyte(G_BASE, (G_FAUCET_DMA + 9)) << 16 | readbyte(G_BASE, (G_FAUCET_DMA + 10)) << 8 | readbyte(G_BASE, (G_FAUCET_DMA + 11)))


; Payload configuration constants
.definelabel G_PAYLOAD_VROM,  0x03800000
.definelabel G_PAYLOAD_SIZE,  0x30000
.definelabel G_PAYLOAD_END,   0x80780000
.definelabel G_PAYLOAD_ADDR,  (G_PAYLOAD_END - G_PAYLOAD_SIZE)

; Subset of payload reserved for "C heap"
.definelabel G_C_HEAP_SIZE,   0x8000
.definelabel G_C_HEAP,        (G_PAYLOAD_END - G_C_HEAP_SIZE)
