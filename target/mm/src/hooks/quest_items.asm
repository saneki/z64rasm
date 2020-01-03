;==================================================================================================
; Quest Item Inventory Checks (Near Door)
;==================================================================================================

.headersize (G_CODE_RAM - G_CODE_FILE)

; Lookup type 0 (Room Key)
; Replaces:
;   lui     t7, 0x801F
;   addiu   at, r0, 0x002D
;   addu    t7, t7, t6
;   lbu     t7, 0xF6E0 (t7)
;   beq     t7, at, 0x801329F8
.org 0x80132994
    sw      a1, 0x0024 (sp)
    addiu   a1, r0, 0x002D
    jal     quest_items_door_check_hook
    or      a2, t6, r0
    bnez    t0, 0x801329F8

; Lookup type 1 (Kafei Letter)
; Replaces:
;   lui     t9, 0x801F
;   addiu   at, r0, 0x002F
;   addu    t9, t9, t8
;   lbu     t9, 0xF6E0 (t9)
;   beq     t9, at, 0x801329F8
.org 0x801329B8
    sw      a1, 0x0024 (sp)
    addiu   a1, r0, 0x002F
    jal     quest_items_door_check_hook
    or      a2, t8, r0
    bnez    t0, 0x801329F8
