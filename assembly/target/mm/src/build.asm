.n64
.relativeinclude on

.create "../roms/patched.z64", 0
.incbin "../roms/base.z64"

;==================================================================================================
; Constants
;==================================================================================================

;.include "constants.asm"
.include "addresses.asm"

;==================================================================================================
; Base game editing region
;==================================================================================================

.include "boot.asm"
.include "hacks.asm"
.include "hooks.asm"
.include "hooks_dpad.asm"

;==================================================================================================
; New code region
;==================================================================================================

.headersize (0x80784600 - 0x02F00000)

.org 0x80784600
.area 0x1BA00 //payload max memory
PAYLOAD_START:

.include "init.asm"
.include "every_frame.asm"
.include "dpad.asm"
.importobj "../build/bundle.o"
.align 8
DPAD_TEXTURE:
.incbin("../../../resources/dpad.bin")

.align 0x10
PAYLOAD_END:
.endarea //payload max memory

.close
