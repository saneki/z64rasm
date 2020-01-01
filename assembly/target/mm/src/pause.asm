pause_menu_item_select_draw_icon_hook:
    addiu   sp, sp, -0x20
    sw      ra, 0x0018 (sp)

    ; Move parameter 5 (vertices index for Quadrangle)
    lw      at, 0x0030 (sp)
    sw      at, 0x0010 (sp)

    ; Parameter 6 (Vertex buffer index)
    sw      s2, 0x0014 (sp)

    jal     pause_menu_item_select_draw_icon
    ; Overwrite A1 with item Id in V0 (we can calculate A1 with it later)
    or      a1, v0, r0

    lw      ra, 0x0018 (sp)

    jr      ra
    addiu   sp, sp, 0x20
