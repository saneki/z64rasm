savedata_after_load_hook:
    lw      a0, 0x0000 (sp)
    j       savedata_after_load
    lw      a1, 0x0004 (sp)

savedata_after_prepare_hook:
    j       savedata_after_prepare
    ; Displaced code (stack adjustment)
    addiu   sp, sp, 0x30
