before_game_state_update_hook:
    ; Displaced code
    sb      r0, 0x00A3 (a1)
    sw      a1, 0x001C (sp)

    addiu   sp, sp, -0x18
    sw      ra, 0x10 (sp)

    jal     before_game_state_update
    nop

    lw      ra, 0x10 (sp)
    addiu   sp, sp, 0x18

    jr      ra
    nop
