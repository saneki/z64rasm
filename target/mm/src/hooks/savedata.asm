;==================================================================================================
; Savedata Hooks
;==================================================================================================

.headersize(G_CODE_RAM - G_CODE_FILE)

; Hook after loading savedata.
; Replaces:
;   jr      ra
.org 0x80145464
    j       savedata_after_load_hook
