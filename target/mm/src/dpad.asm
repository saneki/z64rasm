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
