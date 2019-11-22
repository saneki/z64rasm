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
; Magic meter color hooks
;==================================================================================================

; Custom color for infinite magic (original: #0000C8)
; Replaces:
;   lh      t8, 0x0272 (t1)
;   andi    t9, t8, 0x00FF
;   ori     t6, t9, 0xC800
.orga 0xAFCEA4 ; In memory: 0x80116E44
    jal     get_magic_meter_color_hook
    ori     a0, r0, 1
    ; Restore RA from previous stack value
    lw      ra, -0x0004 (sp)

; Custom color for normal magic (original: #00C800)
; Replaces:
;   lh      t8, 0x0272 (t1)
;   andi    t9, t8, 0x00FF
;   or      t6, t9, at
.orga 0xAFCED4 ; In memory: 0x80116E74
    jal     get_magic_meter_color_hook
    ori     a0, r0, 0
    ; Restore RA from previous stack value
    lw      ra, -0x0004 (sp)

;==================================================================================================
; Map color hooks
;==================================================================================================

; Custom color for map (original: #00FFFFA0)
; Replaces:
;   andi    t6, t9, 0x00FF
;   or      t5, t8, t6
.orga 0xAE9354 ; In memory: 0x801032F4
    jal     get_map_color_hook
    nop

; Custom color for player cursor (original: #C8FF00)
; Replaces:
;   andi    t9, t5, 0x00FF
;   or      t7, t9, at
.orga 0xAE9EEC ; In memory: 0x80103E8C
    jal     get_map_player_cursor_color_hook
    nop

; Custom color for entrance cursor (original: #C80000)
; Replaces:
;   andi    t4, t3, 0x00FF
;   or      t5, t4, at
.orga 0xAEC430 ; In memory: 0x801063D0
    jal     get_map_entrance_cursor_color_hook
    nop
