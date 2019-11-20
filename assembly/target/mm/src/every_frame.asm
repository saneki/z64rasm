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
    addiu   sp, sp, -0x10
    sw      ra, 0 (sp)

    ; Store modified regs prior to hook
    sw      s0, 4 (sp)
    sw      s1, 8 (sp)

    jal before_non_menu_update
    nop

    ; Restore modified regs
    lw      s0, 4 (sp)
    lw      s1, 8 (sp)

    ; Displaced code
    lw      t6, 0x0A74 (s0)
    addiu   at, r0, 0xFFEF

    lw      ra, 0 (sp)
    jr      ra
    addiu   sp, sp, 0x10

before_damage_process_hook:
    addiu   sp, sp, -0x10
    sw      ra, 0 (sp)
    sw      a0, 4 (sp)

    jal     before_damage_process
    nop

    bnez    v0, before_damage_process_hook_caller_return
    nop

    lw      s0, 4 (sp)
    lw      ra, 0 (sp)
    jr      ra
    addiu   sp, sp, 0x10

before_damage_process_hook_caller_return:
    ; Will be returning from caller function, so restore S0
    addiu   sp, sp, 0x10
    lw      s0, 0x0028 (sp)

    ; Restore RA from caller's caller function
    lw      ra, 0x002C (sp)

    ; Fix stack for caller and return
    jr ra
    addiu   sp, sp, 0x78
