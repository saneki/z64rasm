misc_crit_wiggle_check_hook:
    addiu   sp, sp, -0x20
    sw      ra, 0x0018 (sp)
    sw      a0, 0x0010 (sp)
    sw      a1, 0x0014 (sp)

    or      a0, s0, r0
    jal     misc_crit_wiggle_check
    or      a1, v1, r0

    ; Move result to AT
    or      at, v0, r0

    lw      ra, 0x0018 (sp)
    lw      a0, 0x0010 (sp)
    lw      a1, 0x0014 (sp)

    jr      ra
    addiu   sp, sp, 0x20
