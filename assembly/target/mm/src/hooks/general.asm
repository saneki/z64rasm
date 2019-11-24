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
; Damage processing hook
;==================================================================================================

; Replaces:
;   sw      s0, 0x0028 (sp)
;   or      s0, a0, r0
;   sw      ra, 0x002C (sp)
.orga 0xBFE594 ; In memory: 0x80751A94
    sw      ra, 0x002C (sp)
    jal     before_damage_process_hook
    sw      s0, 0x0028 (sp)

;==================================================================================================
; Override floor physics type hook
;==================================================================================================

; Replaces:
;   jal     0x800C99D4
.orga 0xC0DAA0 ; In memory: 0x80760FA0
    jal     override_get_floor_physics_type

;==================================================================================================
; Main Menu draw hook
;==================================================================================================

; Replaces:
;   sw      s0, 0x0020 (sp)
;   or      s0, a0, r0
;   sw      ra, 0x0024 (sp)
.orga 0xBDD26C ; In memory: 0x8077E3BC
    sw      ra, 0x0024 (sp)
    jal     before_main_menu_draw_hook
    sw      s0, 0x0020 (sp)
