; If in Deku mode and reset_magic is 0 for even one frame, this will set the Deku B button value
; to 0xFD. Setting the reset_magic back to 1 will *not restore the Deku B button value* for some
; reason.
;
; This fix changes the code to check that both magic_reset and has_magic are 0 before removing the
; Deku B button.

fix_deku_has_magic_check:
    ; T0 holds z64_file pointer (0x801EF670)
    lbu      t7, 0x0040 (t0) ; magic_reset byte
    lbu      t2, 0x0038 (t0) ; has_magic byte

    ; If either magic_reset or has_magic is non-0, this value should be non-0
    or       t7, t7, t2

    ; Simulate branch instruction that we overwrote
    bnezl    t7, jump_0x80110728
    nop

    ; Jump (not taking branch)
    j        0x801106A0
    nop

jump_0x80110728:
    ; Jump (taking branch)
    j        0x80110728
    nop
