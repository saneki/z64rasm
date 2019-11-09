dpad_draw:
    addiu   sp, sp, -0x10
    sw      ra, 0 (sp)

    jal     draw_dpad
    nop

    lw      ra, 0 (sp)
    addiu   sp,sp, 0x10

    jr      ra
    ; Displaced code
    lw      t6, 0x0068 (sp)

dpad_handle:
    addiu   sp, sp, -0x10
    sw      ra, 0 (sp)

    ; Displaced code (preserve a0)
    sw      a0, 4 (sp)

    jal     handle_dpad
    nop

    ; Displaced code (restore to s0)
    lw      s0, 4 (sp)

    lw      ra, 0 (sp)
    addiu   sp, sp, 0x10

    jr ra
    nop
