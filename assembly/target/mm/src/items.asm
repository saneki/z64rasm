items_after_receive_hook:
    lw      a0, 0x0000 (sp)
    lw      a1, 0x0004 (sp)

    addiu   sp, sp, -0x10
    sw      ra, 0x0000 (sp)

    jal     items_after_receive
    sw      v0, 0x0004 (sp)

    lw      ra, 0x0000 (sp)
    lw      v0, 0x0004 (sp)

    jr      ra
    addiu   sp, sp, 0x10

items_after_removal_hook:
    lw      a0, 0x0000 (sp)

    j       items_after_removal
    lw      a1, 0x0004 (sp)
