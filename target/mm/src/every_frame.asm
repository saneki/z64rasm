;before_game_state_update_hook:
;    ; Displaced code
;    sb      r0, 0x00A3 (a1)
;    sw      a1, 0x001C (sp)
;
;    addiu   sp, sp, -0x18
;    sw      ra, 0x10 (sp)
;
;    jal     before_game_state_update
;    nop
;
;    lw      ra, 0x10 (sp)
;    addiu   sp, sp, 0x18
;
;    jr      ra
;    nop

before_non_menu_update_hook:
    addiu   sp, sp, -0x20
    sw      ra, 0x0010 (sp)

    ; Store modified regs prior to hook
    sw      s0, 0x0014 (sp)
    sw      s1, 0x0018 (sp)

    jal before_non_menu_update
    nop

    ; Restore modified regs
    lw      s0, 0x0014 (sp)
    lw      s1, 0x0018 (sp)

    ; Displaced code
    lw      t6, 0x0A74 (s0)
    addiu   at, r0, 0xFFEF

    lw      ra, 0x0010 (sp)

    jr      ra
    addiu   sp, sp, 0x20
