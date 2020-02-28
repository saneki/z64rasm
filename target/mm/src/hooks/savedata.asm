;==================================================================================================
; Savedata Hooks
;==================================================================================================

.headersize(G_CODE_RAM - G_CODE_FILE)

; Hook after loading savedata.
; Replaces:
;   jr      ra
.org 0x80145464
    j       savedata_after_load_hook

; Hook after preparing savedata.
; Replaces:
;   lw      s5, 0x0028 (sp)
;   jr      ra
;   addiu   sp, sp, 0x30
.org 0x80144568
    or      a0, s5, r0
    j       savedata_after_prepare_hook
    lw      s5, 0x0028 (sp)
