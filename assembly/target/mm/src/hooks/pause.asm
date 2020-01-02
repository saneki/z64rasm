;==================================================================================================
; Pause Menu Icon Draw
;==================================================================================================

.headersize(G_KALEIDO_VRAM - G_KALEIDO_FILE)

; Hook draw for item textures on "Select Item" screen.
; Replaces:
;   jal     0x80821AD4
.org 0x8081BB70 ; In RDRAM: 0x807509F0
    jal     pause_menu_item_select_draw_icon_hook

; Remove relocations.
.org 0x8082C944
    .dw 0x00000000 ; Removes: 0x44005AD0
