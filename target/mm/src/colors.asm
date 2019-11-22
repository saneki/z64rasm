get_magic_meter_color_hook:
    addiu   sp, sp, -0x18
    sw      ra, 0x0000 (sp)
    sw      a1, 0x0004 (sp)
    sw      v0, 0x0008 (sp)
    sw      t3, 0x000C (sp)
    sw      t5, 0x0010 (sp)

    ; A bit gross, RA will be restored from stack after call
    lui     ra, 0x0400
    ori     ra, ra, 0x0400
    sw      ra, 0x0014 (sp)

    jal     get_magic_meter_color
    nop

    ; Also a bit gross, put return value in T6
    or      t6, v0, r0

    lw      ra, 0x0000 (sp)
    lw      a1, 0x0004 (sp)
    lw      v0, 0x0008 (sp)
    lw      t3, 0x000C (sp)
    lw      t5, 0x0010 (sp)
    addiu   sp, sp, 0x18

    lw      v1, 0x00DC (sp)
    lw      t1, 0x004C (sp)
    lh      t2, 0x00E2 (sp)

    jr      ra
    nop

get_map_color_hook:
    addiu   sp, sp, -0x10
    sw      ra, 0x0000 (sp)
    sw      a1, 0x0004 (sp)
    sw      v1, 0x0008 (sp)

    jal     get_map_color
    nop

    ; Put return value in T5
    or      t5, v0, r0

    lw      ra, 0x0000 (sp)
    lw      a1, 0x0004 (sp)
    lw      v1, 0x0008 (sp)

    jr      ra
    addiu   sp, sp, 0x10

get_map_player_cursor_color_hook:
    addiu   sp, sp, -0x10
    sw      ra, 0x0000 (sp)
    sw      v0, 0x0004 (sp)
    sw      t0, 0x0008 (sp)
    sw      t8, 0x000C (sp)

    jal     get_map_player_cursor_color
    nop

    ; Put return value in T7
    or      t7, v0, r0

    lw      ra, 0x0000 (sp)
    lw      v0, 0x0004 (sp)
    lw      t0, 0x0008 (sp)
    lw      t8, 0x000C (sp)

    jr      ra
    addiu   sp, sp, 0x10

get_map_entrance_cursor_color_hook:
    addiu   sp, sp, -0x10
    sw      ra, 0x0000 (sp)
    sw      v0, 0x0004 (sp)
    sw      t0, 0x0008 (sp)
    sw      t8, 0x000C (sp)

    jal     get_map_entrance_cursor_color
    nop

    ; Put return value in T5
    or      t5, v0, r0

    lw      ra, 0x0000 (sp)
    lw      v0, 0x0004 (sp)
    lw      t0, 0x0008 (sp)
    lw      t8, 0x000C (sp)

    jr      ra
    addiu   sp, sp, 0x10
