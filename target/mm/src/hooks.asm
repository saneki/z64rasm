;==================================================================================================
; Every frame hooks
;==================================================================================================

; Runs before the game state update function
; Replaces:
;   sb      r0, 0x00A3 (a1)
;   sw      a1, 0x001C (sp)
;.orga 0xB5A8D4 ; In memory: 0x80174874
;    jal     before_game_state_update_hook
;    nop

; Runs after the game state update function
; Replaces:
;   jr      ra
;   nop
;.orga 0xB5A8F8 ; In memory: 0x80174898
;    j       after_game_state_update
;    nop

;==================================================================================================
; Non-menu processing hooks
;==================================================================================================

; Runs when in the "main game" (and not using the menu)
; Replaces:
;   lw      t6, 0x0A74 (s0)
;   addiu   at, r0, 0xFFEF
.orga 0xC10060 ; In memory: 0x80763560
    jal     before_non_menu_update_hook
    nop

;==================================================================================================
; Override floor physics type hook
;==================================================================================================

; Replaces:
;   jal     0x800C99D4
.orga 0xC0DAA0 ; In memory: 0x80760FA0
    jal     override_get_floor_physics_type
