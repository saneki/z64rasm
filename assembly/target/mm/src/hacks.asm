;==================================================================================================
; DPad Not-on-C-Buttons Fixes
;==================================================================================================

; Remove C button check for equipped mask, fixes using B button item (usually sword).
; Replaces:
;   jal     0x8074D19C
.orga 0xBF9E14 ; In memory: 0x8074D314 (file offset: 0x23F4)
    addiu   v0, r0, 1

; For some items, if UseItem is called without said item being on the C-buttons,
; it will be automatically called again to unequip. Prevents this.
; Replaces:
;   jal     0x8074EE20
.orga 0xBF9EAC ; In memory: 0x8074D3AC (file offset: 0x248C)
    nop

; Remove relocations.
.orga 0xC28898 ; In memory: 0x8077BD98 (file offset: 0x30E78)
.dw 0x00000000 ; Replaces: 0x440023F4
.orga 0xC288A0 ; In memory: 0x8077BDA0 (file offset: 0x30E80)
.dw 0x00000000 ; Replaces: 0x4400248C

;==================================================================================================
; Draw C Button Amounts Fix
;==================================================================================================
;
; Fixes B & C button item amounts and text being drawn in green if magic has not yet been obtained.

; Fix for B button icon.
; Replaces:
;   jal     0x80118084
.orga 0xB06274 ; In memory: 0x80120214
    jal     draw_b_button_icon_color_fix

; Fix for C button icons.
; Replaces:
;   jal     0x80118890
.orga 0xB0627C ; In memory: 0x8012021C
    jal     draw_c_button_icons_color_fix

;==================================================================================================
; Underwater Ocarina
;==================================================================================================

; Replaces:
;   andi    t7, a2, 0x00FF
;   slti    at, t7, 0x0012
.orga 0xAF6974 ; In memory: 0x80110914
    jal     underwater_ocarina_check
    andi    t7, a2, 0x00FF
