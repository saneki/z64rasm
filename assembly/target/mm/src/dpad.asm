dpad_draw_hook:
    addiu   sp, sp, -0x10
    sw      ra, 0x0000 (sp)

    jal     dpad_draw
    nop

    lw      ra, 0x0000 (sp)
    addiu   sp, sp, 0x10

    jr      ra
    ; Displaced code
    lw      t6, 0x0068 (sp)

dpad_handle_hook:
    addiu   sp, sp, -0x10
    sw      ra, 0x0000 (sp)

    jal     dpad_handle
    ; Displaced code (preserve a0)
    sw      a0, 0x0004 (sp)

    bnez    v0, @@caller_return
    nop

    lw      ra, 0x0000 (sp)

    ; Displaced code (restore to s0)
    lw      s0, 0x0004 (sp)

    jr      ra
    addiu   sp, sp, 0x10

; Used to return early from the hooked function 0x8074D29C if we called z64_UseItem.
; This is because z64_UseItem sets a byte (0x803FFDB0 +0x14A) which is the item Link currently has out.
; Because our hook is at the start of the function, this value may be set earlier than expected.
;
; Specifically, the branch at 0x8074D408 won't be taken, and can lead to a crash in specific conditions.
; This has been noted to happen when not having an item on the B button while wearing a mask with a B button
; effect (Blast, Bremen, Kamaro), and calling z64_UseItem.
;
; To fix this, we return non-zero if z64_UseItem was called, and if so return from the caller function
; immediately.
@@caller_return:
    ; Will be returning from caller function, so restore S0
    addiu   sp, sp, 0x10
    lw      s0, 0x0030 (sp)

    ; Restore RA from caller's caller function
    lw      ra, 0x0034 (sp)

    ; Fix stack for caller and return
    jr      ra
    addiu   sp, sp, 0x50
