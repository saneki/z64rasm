;==================================================================================================
; Pushblock Speed
;==================================================================================================

.headersize(G_OBJ_OSHIHIKI_VRAM - G_OBJ_OSHIHIKI_FILE)

; Replaces:
;   sw      a1, 0x0004 (sp)
;   lhu     t6, 0x0160 (a0)
;   lui     at, 0x4000
;   mtc1    r0, f4
;   mtc1    at, f6
.org 0x80918314
    or      at, ra, r0
    jal     misc_get_push_block_speed_hook
    sw      a1, 0x0004 (sp)
    or      ra, at, r0
    lhu     t6, 0x0160 (a0)

;==================================================================================================
; Iceblock Push Speed
;==================================================================================================

.headersize(G_OBJ_ICEBLOCK_VRAM - G_OBJ_ICEBLOCK_FILE)

; Actor: 0x143 (Obj_Iceblock)
; Actor File VRAM: 0x80A23090

; Replaces:
;   lui     at, 0x4060       ; Clamp constant
;   mtc1    at, f12
;   lui     at, 0x80A2
;   lwc1    f18, 0x707C (at) ; Additive velocity
;   lui     at, 0x80A2
;   lwc1    f6, 0x7080 (at)  ; Initial velocity
.org 0x80A25E9C
    or      a0, s0, r0
    jal     misc_get_iceblock_push_speed_hook
    lw      a1, 0x004C (sp)
    nop
    nop
    nop

; Remove relocations for hook.
.org 0x80A273C4
.area 0x10, 0
    .dw 0x00000000 ; Replaces: 0x45002E14
    .dw 0x00000000 ; Replaces: 0x46002E18
    .dw 0x00000000 ; Replaces: 0x45002E1C
    .dw 0x00000000 ; Replaces: 0x46002E20
.endarea

;==================================================================================================
; Great Bay Temple Faucets
;==================================================================================================

.headersize(G_BG_DBLUE_MOVEBG_VRAM - G_BG_DBLUE_MOVEBG_FILE)

; Actor: 0x174 (Bg_Dblue_Movebg)

; Adjust speed of one-way faucet.
; Replaces:
;   addiu   sp, sp, -0x28
;   sw      s0, 0x0018 (sp)
;   or      s0, a0, r0
;   sw      ra, 0x001C (sp)
;   sw      a1, 0x002C (sp)
;   lw      t6, 0x002C (sp)
;   lh      t7, 0x0188 (s0)
;   addiu   t9, r0, 0x0005
;   lw      a3, 0x1CCC (t6)
;   addiu   t8, t7, 0x0001
;   sh      t8, 0x0188 (s0)
;   lh      v0, 0x0188 (s0)
;   addiu   a0, s0, 0x018A
;   addiu   a1, r0, 0x0384
;   slti    at, v0, 0x0006
.org 0x80A2A444
.area 0x3C, 0
    addiu   sp, sp, -0x28
    sw      s0, 0x0018 (sp)
    sw      ra, 0x001C (sp)
    ; Return values in T8 (acceleration) and T9 (max velocity)
    jal     misc_get_great_bay_temple_faucet_speed_hook
    sw      a1, 0x002C (sp)
    lw      t6, 0x002C (sp)
    lh      t7, 0x0188 (s0)
    lw      a3, 0x1CCC (t6)
    addu    t8, t8, t7
    sh      t8, 0x0188 (s0)
    lh      v0, 0x0188 (s0)
    addiu   a0, s0, 0x018A
    addiu   a1, r0, 0x0384
    addiu   t5, t9, 1
    slt     at, v0, t5
.endarea

; Adjust speed on two-way faucet.
; Replaces:
;   addiu   sp, sp, -0x30
;   sw      s0, 0x0018 (sp)
;   or      s0, a0, r0
;   sw      ra, 0x001C (sp)
;   sw      a1, 0x0034 (sp)
;   lw      t6, 0x0034 (sp)
;   lh      t7, 0x0188 (s0)
;   addiu   t9, r0, 0x0005
;   lw      v1, 0x1CCC (t6)
;   addiu   t8, t7, 0x0001
;   sh      t8, 0x0188 (s0)
;   lh      v0, 0x0188 (s0)
;   addiu   a0, s0, 0x018A
;   addiu   a1, r0, 0x0384
;   slti    at, v0, 0x0006
.org 0x80A2A7F8
.area 0x3C, 0
    addiu   sp, sp, -0x30
    sw      s0, 0x0018 (sp)
    sw      ra, 0x001C (sp)
    ; Return values in T8 (acceleration) and T9 (max velocity)
    jal     misc_get_great_bay_temple_faucet_speed_hook
    sw      a1, 0x0034 (sp)
    lw      t6, 0x0034 (sp)
    lh      t7, 0x0188 (s0)
    lw      v1, 0x1CCC (t6)
    addu    t8, t8, t7
    sh      t8, 0x0188 (s0)
    lh      v0, 0x0188 (s0)
    addiu   a0, s0, 0x018A
    addiu   a1, r0, 0x0384
    addiu   t5, t9, 1
    slt     at, v0, t5
.endarea
