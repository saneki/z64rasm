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

;==================================================================================================
; Quest Item Inventory Checks (En_Time_Tag)
;==================================================================================================

.headersize (G_EN_TIME_TAG_VRAM - G_EN_TIME_TAG_FILE)

; Prevent from being kicked out of Inn if Room Key is in storage.
; Replaces:
;   lui     a1, 0x801F
;   addiu   a1, a1, 0xF670
;   addu    t8, a1, t7
;   lbu     t9, 0x0070 (t8)
;   addiu   at, r0, 0x002D
;   beq     t9, at, 0x80ACA998
.org 0x80ACA86C
    or      a1, a2, r0
    addiu   a2, r0, 0x002D
    jal     quest_items_time_tag_check_hook
    or      a3, t7, r0
    or      a2, a1, r0
    bnez    v0, 0x80ACA998
