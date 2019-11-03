;==================================================================================================
; DPAD Display
;==================================================================================================
;
; Replaces:
;   sw      a0, 0x0068 (sp)
;   lw      t6, 0x0068 (sp)
.orga 0xAFE8F8 ; In Memory: 0x80118898
    jal     dpad_draw
    sw      a0, 0x0068 (sp)

; --- Other possible hook ---
; Replaces:
;   sw      s0, 0x0040 (sp)
;   sw      a0, 0x0108 (sp)
;.orga 0xAFD168 ; In Memory: 0x80117108
;    jal     dpad_draw
;    sw      s0, 0x0040 (sp)
