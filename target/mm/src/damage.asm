before_damage_process_hook:
    addiu   sp, sp, -0x10
    sw      ra, 0 (sp)
    sw      a0, 4 (sp)

    jal     before_damage_process
    nop

    bnez    v0, @@caller_return
    nop

    lw      s0, 4 (sp)
    lw      ra, 0 (sp)
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
