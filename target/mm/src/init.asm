init:
    ; Displaced code (stack storage)
    sw      s4, 0x0028 (sp)
    sw      s3, 0x0024 (sp)
    sw      s2, 0x0020 (sp)
    sw      s1, 0x001C (sp)

    addiu   sp, sp, -0x18
    sw      ra, 0x10 (sp)

    jal     c_init
    nop

    ; Displaced code
    lui     s0, 0x801C
    addiu   s0, s0, 0xD910

    lw      ra, 0x10 (sp)
    addiu   sp, sp, 0x18

    jr      ra
    ; Displaced code
    lui     a0, 0x0004