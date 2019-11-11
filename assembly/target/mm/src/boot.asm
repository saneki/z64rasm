; Majora's Mask notes:
;  We can't abuse the extra memory that OoT doesn't use (+4MiB of expansion pack space), since Majora does.
;  However, may be able to use the following region: [0x80780000, 0x807DA800).
;  Everything after 0x807DA800 seems to be used by something until the RAM end (0x80800000).
;
; Console / EverDrive notes:
;  Despite never being used on emulator, apparently [0x80780000, 0x807A9E00) is written to,
;  or unstable or something. [0x807A9E00, 0x807DA800) does seem to be unused/stable.
;
; Add dmatable entries for new code
; Remove the unused files at the bottom the DMA Table
;   - this isn't strictly necessary, but adds flexibility for the future
.orga 0x20580
.area 0x70, 0
    .word 0x02F00000, 0x02F00000 + PAYLOAD_END - PAYLOAD_START, 0x02F00000, 0
.endarea

; Load new code from ROM
; Replaces:
;   sw      s0, 0x0018 (sp)
;   lui     s0, 0x801C
;   addiu   s0, s0, 0xD910
;   sw      ra, 0x002C (sp)
;   sw      s4, 0x0028 (sp)
;   sw      s3, 0x0024 (sp)
;   sw      s2, 0x0020 (sp)
;   sw      s1, 0x001C (sp)
;   sw      a0, 0x0340 (sp)
.orga 0xB5A904 ; In memory: 0x801748A4
.area 0x24, 0
    sw      ra, 0x002C (sp)
    sw      a0, 0x0340 (sp)

    ; Load first code file from ROM
    lui     a0, 0x807A
    ori     a0, a0, 0x9E00
    li      a2, PAYLOAD_END - PAYLOAD_START
    jal     0x80080C90
    lui     a1, 0x02F0

    jal     init
    sw      s0, 0x0018 (sp)
.endarea
