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

get_clock_diamond_color_hook:
    addiu   sp, sp, -0x10
    sw      ra, 0x0000 (sp)
    sw      v0, 0x0004 (sp)
    sw      s0, 0x0008 (sp)

    jal     get_clock_diamond_color
    nop

    ; Put return value in T8
    or      t8, v0, r0

    lw      ra, 0x0000 (sp)
    lw      v0, 0x0004 (sp)
    lw      s0, 0x0008 (sp)

    jr      ra
    addiu   sp, sp, 0x10

get_inverted_clock_diamond_color_r_hook:
    ; Displaced code
    lh      a0, 0xFBCC (a0)

    addiu   sp, sp, -0x18
    sw      ra, 0x0000 (sp)
    sw      a0, 0x0004 (sp)
    sw      s0, 0x0008 (sp)
    sw      t2, 0x000C (sp)

    jal get_inverted_clock_diamond_color
    ori     a0, r0, 0

    ; Put return value in T0
    or      t0, v0, r0

    lw      ra, 0x0000 (sp)
    lw      a0, 0x0004 (sp)
    lw      s0, 0x0008 (sp)
    lw      t2, 0x000C (sp)

    ; Displaced code
    lui     t5, 0x801C

    jr      ra
    addiu   sp, sp, 0x18

get_inverted_clock_diamond_color_g_hook:
    addiu   sp, sp, -0x18
    sw      ra, 0x0000 (sp)
    sw      a0, 0x0004 (sp)
    sw      s0, 0x0008 (sp)
    sw      t2, 0x000C (sp)
    sw      t5, 0x0010 (sp)

    jal get_inverted_clock_diamond_color
    ori     a0, r0, 1

    ; Put return value in A2
    or      a2, v0, r0

    lw      ra, 0x0000 (sp)
    lw      a0, 0x0004 (sp)
    lw      s0, 0x0008 (sp)
    lw      t2, 0x000C (sp)
    lw      t5, 0x0010 (sp)

    ; Displaced code
    lui     a3, 0x801C
    lui     t3, 0x801C

    jr      ra
    addiu   sp, sp, 0x18

get_inverted_clock_diamond_color_b_hook:
    addiu   sp, sp, -0x20
    sw      ra, 0x0000 (sp)
    sw      s0, 0x0004 (sp)
    sw      a3, 0x0008 (sp)
    sw      t2, 0x000C (sp)
    sw      t4, 0x0010 (sp)
    sw      t5, 0x0014 (sp)

    jal get_inverted_clock_diamond_color
    ori     a0, r0, 2

    ; Put return value in A0
    or      a0, v0, r0

    lw      ra, 0x0000 (sp)
    lw      s0, 0x0004 (sp)
    lw      a3, 0x0008 (sp)
    lw      t2, 0x000C (sp)
    lw      t4, 0x0010 (sp)
    lw      t5, 0x0014 (sp)

    jr      ra
    addiu   sp, sp, 0x20
