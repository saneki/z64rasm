;==================================================================================================
; Pause Menu Icon Draw
;==================================================================================================

; Hook draw for item textures on "Select Item" screen.
; Offset: 0x5AD0
; Replaces:
;   jal     0x80821AD4
.orga 0xBE5B40 ; In VRAM: 0x8081BB70 (RDRAM: 0x807509F0)
    jal     pause_menu_item_select_draw_icon_hook

; Remove relocations.
.orga 0xBF6914 ; In VRAM: 0x8082C944‬
.dw 0x00000000 ; Removes: 0x44005AD0
