;==================================================================================================
; File Select Constructor & Destructor
;==================================================================================================

; Replaces:
;   jr      ra
;.orga 0xBDDDE4 ; In VRAM: 0x80813DE4
.orga G_FILESELECT_FILE + 0xFDD4
    j       file_select_hook_after_ctor

; Replaces:
;   jr      ra
;.orga 0xBDDC90 ; In VRAM: 0x80813C90
.orga G_FILESELECT_FILE + 0xFC80
    j       file_select_hook_after_dtor

;==================================================================================================
; File Select Before Draw
;==================================================================================================

; Replaces:
;   sw      s0, 0x0020 (sp)
;   or      s0, a0, r0
;   sw      ra, 0x0024 (sp)
;.orga 0xBDD26C ; In VRAM: 0x8081326C
.orga G_FILESELECT_FILE + 0xF25C
    sw      ra, 0x0024 (sp)
    jal     file_select_before_draw_hook
    sw      s0, 0x0020 (sp)

;==================================================================================================
; File Select Hash
;==================================================================================================

; Replaces:
;   addiu   t6, v0, 0x0008
;   sw      t6, 0x02B0 (a1)
;   sw      r0, 0x0004 (v0)
;.orga 0xBDD890 ; In VRAM: 0x80813890‬
.orga G_FILESELECT_FILE + 0xF880
    sw      r0, 0x0004 (v0)
    jal     file_select_draw_hash_hook
    addiu   t6, v0, 0x0008
