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

;==================================================================================================
; Clock color hooks
;==================================================================================================

; Custom color for clock.
; Replaces:
;   lui     at, 0x00AA
;   ori     at, at, 0x6400
;   addiu   t9, v0, 0x0008
;   sw      t9, 0x02A0 (s0)
;   or      t8, ra, at
.orga 0xB00170 ; In memory: 0x8011A110
    addiu   t9, v0, 0x0008
    sw      ra, -0x0004 (sp)
    jal     get_clock_diamond_color_hook
    sw      t9, 0x02A0 (s0)
    lw      ra, -0x0004 (sp)

; Custom color for inverted clock (red).
; Replaces:
;   addu    t0, t0, t2
;   lh      a0, 0xFBCC (a0)
;   lh      t0, 0xFBEC (t0)
;   lui     t5, 0x801C
.orga 0xAFFB98 ; In memory: 0x80119B38
    sw      ra, -0x0004 (sp)
    jal     get_inverted_clock_diamond_color_r_hook
    nop
    lw      ra, -0x0004 (sp)

; Custom color for inverted clock (green).
; Replaces:
;   lh      t5, 0xFBD0 (t5)
;   lh      a2, 0xFBF0 (a2)
;   lui     a3, 0x801C
;   lui     t3, 0x801C
.orga 0xAFFC64 ; In memory: 0x80119C04
    sw      ra, -0x0004 (sp)
    jal     get_inverted_clock_diamond_color_g_hook
    lh      t5, 0xFBD0 (t5)
    lw      ra, -0x0004 (sp)

; Custom color for inverted clock (blue).
; Replaces:
;   lui     a0, 0x801C
;   addu    a0, a0, t2
;   lh      a3, 0xFBD4 (a3)
;   lh      a0, 0xFBF4 (a0)
.orga 0xAFFD28 ; In memory: 0x80119CC8
    sw      ra, -0x0004 (sp)
    jal     get_inverted_clock_diamond_color_b_hook
    lh      a3, 0xFBD4 (a3)
    lw      ra, -0x0004 (sp)

; Custom color for clock diamond sun icon.
; Replaces:
;   lui     at, 0xFFFF
;   ori     at, at, 0x6E00
;   andi    t9, t7, 0x00FF
;   or      t6, t9, at
.orga 0xB003FC ; In memory: 0x8011A39C
    or      a3, t7, r0
    jal     get_clock_diamond_sun_color_hook
    swc1    f2, 0x01D0 (sp)
    lwc1    f2, 0x01D0 (sp)

; Custom color for clock diamond sun icon (blinking).
; Replaces:
;   lui     at, 0xFFFF
;   addiu   t8, v0, 0x0008
;   sw      t8, 0x02A0 (s0)
;   sw      t7, 0x0000 (v0)
;   lh      t9, 0x0000 (a1)
;   ori     at, at, 0x6E00
;   andi    t6, t9, 0x00FF
;   or      t8, t6, at
.orga 0xB00420 ; In memory: 0x8011A3C0
    addiu   t8, v0, 0x0008
    sw      t8, 0x02A0 (s0)
    sw      t7, 0x0000 (v0)
    lh      a3, 0x0000 (a1)
    jal     get_clock_diamond_sun_color_hook
    swc1    f2, 0x01D0 (sp)
    lwc1    f2, 0x01D0 (sp)
    ; Move return value from T6 to T8
    or      t8, t6, r0

; Custom color for clock sun icon.
; Replaces:
;   ori     at, at, 0x6E00
;   andi    t8, t6, 0x00FF
;   or      t7, t8, at
.orga 0xB0079C ; In memory: 0x8011A73C
    jal     get_clock_sun_color_hook
    sh      t0, 0x01C6 (sp)
    lh      t0, 0x01C6 (sp)

; Custom color for clock moon icon.
; Replaces:
;   ori     at, at, 0x3700
;   andi    t9, t7, 0x00FF
;   or      t6, t9, at
.orga 0xB008EC ; In memory: 0x8011A88C
    jal     get_clock_moon_color_hook
    sh      t0, 0x01C6 (sp)
    lh      t0, 0x01C6 (sp)

;==================================================================================================
; A, B, C buttons color hooks
;==================================================================================================

; Custom color for A button.
; Replaces:
;   andi    t4, t3, 0x00FF
;   or      t5, t4, at
.orga 0xAFEE5C ; In memory: 0x80118DFC
    jal     get_a_button_color_hook
    nop

; Custom color for B button.
; Replaces:
;   addiu   t8, r0, 0x0078
;   ori     at, at, 0x69E8
;   addiu   t7, r0, 0x0064
;   addiu   t6, r0, 0x00FF
.orga 0xAFD200 ; In memory: 0x801171A0
    jal     get_b_button_color_hook
    ori     at, at, 0x69E8
    andi    t6, t6, 0x00FF
    andi    t8, t8, 0x00FF

; Custom colors for C buttons and Start button.
; Replaces:
;   lh      t8, 0x002A (sp)
;   or      t9, t6, t7
;   andi    t6, t8, 0x00FF
;   or      t7, t9, t6
.orga 0xAF346C ; In memory: 0x8010D40C
    sw      ra, -0x0004 (sp)
    jal     get_c_start_button_color_hook
    lh      t8, 0x002A (sp)
    lw      ra, -0x0004 (sp)

;==================================================================================================
; Heart colors hooks
;==================================================================================================

; Custom colors for hearts.
; Replaces:
;   jal     0x8010069C
.orga 0xB07594 ; In memory: 0x80121534
    jal     update_heart_colors

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
