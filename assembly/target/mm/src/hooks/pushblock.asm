;==================================================================================================
; Pushblock Speed
;==================================================================================================

; Replaces:
;   sw      a1, 0x0004 (sp)
;   lhu     t6, 0x0160 (a0)
;   lui     at, 0x4000
;   mtc1    r0, f4
;   mtc1    at, f6
.orga 0xCDAF14 ; VROM: 0xD8B3F4
    or      at, ra, r0
    jal     misc_get_push_block_speed_hook
    sw      a1, 0x0004 (sp)
    or      ra, at, r0
    lhu     t6, 0x0160 (a0)
