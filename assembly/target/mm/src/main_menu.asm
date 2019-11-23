before_main_menu_draw_hook:
    addiu   sp, sp, -0x10
    sw      ra, 0x0000 (sp)
    sw      a0, 0x0004 (sp)

    jal     before_main_menu_draw
    nop

    lw      ra, 0x0000 (sp)
    lw      a0, 0x0004 (sp)

    ; Displaced code
    or      s0, a0, r0

    jr      ra
    addiu   sp, sp, 0x10
