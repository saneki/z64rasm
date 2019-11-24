;==================================================================================================
; DPad Not-on-C-Buttons Fixes
;==================================================================================================

; Remove C button check for equipped mask, fixes using B button item (usually sword).
; Replaces:
;   jal 0x8074D19C
.orga 0xBF9E14 ; In memory: 0x8074D314
    nop

; For some items, if UseItem is called without said item being on the C-buttons,
; it will be automatically called again to unequip. Prevents this.
; Replaces:
;   jal 0x8074EE20
.orga 0xBF9EAC ; In memory: 0x8074D3AC
    nop

;==================================================================================================
; Draw C Button Amounts Fix
;==================================================================================================

; Fixes C button item amounts being drawn in green if magic has not yet been obtained.
; Replaces:
;   jal     0x80117BD0
.orga 0xAFE9F8 ; In memory: 0x80118998
    jal     draw_button_amounts_fix

; Same as above but for the B button (needed for mid-air Deku nuts).
; Replaces:
;   jal     0x80117BD0
.orga 0xAFE204 ; In memory: 0x801181A4
    jal     draw_button_amounts_fix
