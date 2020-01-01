;==================================================================================================
; Every frame hooks
;==================================================================================================

; Runs before the game state update function
; Replaces:
;   sb      r0, 0x00A3 (a1)
;   sw      a1, 0x001C (sp)
;.org 0x80174874 ; In rom: 0xB5A8D4
;    jal     before_game_state_update_hook
;    nop

; Runs after the game state update function
; Replaces:
;   jr      ra
;   nop
;.org 0x80174898 ; In rom: 0xB5A8F8
;    j       after_game_state_update
;    nop

;==================================================================================================
; Non-menu processing hooks
;==================================================================================================

; Runs when in the "main game" (and not using the menu)
; Replaces:
;   lw      t6, 0x0A74 (s0)
;   addiu   at, r0, 0xFFEF
.orga G_PLAYER_FILE + 0x18640 ; In memory: 0x80763560
    jal     before_non_menu_update_hook
    nop

;==================================================================================================
; Damage processing hook
;==================================================================================================

; Replaces:
;   sw      s0, 0x0028 (sp)
;   or      s0, a0, r0
;   sw      ra, 0x002C (sp)
.orga G_PLAYER_FILE + 0x6B74 ; In memory: 0x80751A94
    sw      ra, 0x002C (sp)
    jal     before_damage_process_hook
    sw      s0, 0x0028 (sp)

;==================================================================================================
; Override floor physics type hook
;==================================================================================================

; Replaces:
;   jal     0x800C99D4
.orga G_PLAYER_FILE + 0x16080 ; In memory: 0x80760FA0
    jal     override_get_floor_physics_type