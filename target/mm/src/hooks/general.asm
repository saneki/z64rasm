;==================================================================================================
; Player actor update hooks
;==================================================================================================

.headersize (G_PLAYER_ACTOR_VRAM - G_PLAYER_ACTOR_FILE)

; Runs when in the "main game" (and not using the menu)
; Replaces:
;   lw      t6, 0x0A74 (s0)
;   addiu   at, r0, 0xFFEF
.org 0x808460D0 ; In RDRAM: 0x80763560
    jal     before_player_actor_update_hook
    nop

;==================================================================================================
; Damage processing hook
;==================================================================================================

; Replaces:
;   sw      s0, 0x0028 (sp)
;   or      s0, a0, r0
;   sw      ra, 0x002C (sp)
.org 0x80834604 ; In RDRAM: 0x80751A94
    sw      ra, 0x002C (sp)
    jal     before_damage_process_hook
    sw      s0, 0x0028 (sp)

;==================================================================================================
; Override floor physics type hook
;==================================================================================================

; Replaces:
;   jal     0x800C99D4
.org 0x80843B10 ; In RDRAM: 0x80760FA0
    jal     override_get_floor_physics_type

;==================================================================================================
; Song of Time hooks
;==================================================================================================

.headersize (G_CODE_RAM - G_CODE_FILE)

; Replaces:
;   lw      s5, 0x0028 (sp)
;   jr      ra
;   addiu   sp, sp, 0x30
.org 0x80144568
    or      a0, s5, r0
    j       after_song_of_time_clear_hook
    lw      s5, 0x0028 (sp)
