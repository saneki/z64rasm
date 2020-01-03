quest_items_door_check_hook:
    addiu   sp, sp, -0x10
    sw      ra, 0x0000 (sp)

    jal     quest_items_door_check
    sw      a0, 0x0004 (sp)

    lw      ra, 0x0000 (sp)
    lw      a0, 0x0004 (sp)

    ; Move return value into T0
    or      t0, v0, r0

    ; Load back into A1, A2, V0, V1
    lw      a1, 0x0034 (sp)
    lw      v0, 0x0000 (a1)
    lbu     v1, 0x0001 (v0)
    or      a2, v0, r0

    jr      ra
    addiu   sp, sp, 0x10
