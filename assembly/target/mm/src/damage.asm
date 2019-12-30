before_damage_process_hook:
    ; Displaced code
    or      s0, a0, r0

    addiu   sp, sp, -0x10
    sw      ra, 0x0000 (sp)
    sw      a0, 0x0004 (sp)

    jal     before_damage_process
    sw      a1, 0x0008 (sp)

    bnez    v0, @@caller_return
    nop

    lw      ra, 0x0000 (sp)
    lw      a0, 0x0004 (sp)
    lw      a1, 0x0008 (sp)

    jr      ra
    addiu   sp, sp, 0x10

@@caller_return:
    ; Will be returning from caller function, so restore S0
    addiu   sp, sp, 0x10
    lw      s0, 0x0028 (sp)

    ; Restore RA from caller's caller function
    lw      ra, 0x002C (sp)

    ; Fix stack for caller and return
    jr ra
    addiu   sp, sp, 0x78
