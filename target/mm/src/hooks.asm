;==================================================================================================
; Every frame hooks
;==================================================================================================

; Runs before the game state update function
; Replaces:
;   sb      r0, 0x00A3 (a1)
;   sw      a1, 0x001C (sp)
.orga 0xB5A8D4 ; In memory: 0x80174874
    jal     before_game_state_update_hook
    nop

; Runs after the game state update function
; Replaces:
;   jr      ra
;   nop
.orga 0xB5A8F8 ; In memory: 0x80174898
    j       after_game_state_update
    nop
