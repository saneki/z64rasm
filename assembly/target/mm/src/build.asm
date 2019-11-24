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
.include "hooks/colors.asm"
.include "hooks/dpad.asm"
.include "hooks/general.asm"

;==================================================================================================
; New code region
;==================================================================================================

.headersize (0x807A9E00 - 0x03800000)

.org 0x807A9E00
.area 0xE200 //payload max memory
PAYLOAD_START:

.include "init.asm"
.include "every_frame.asm"
.include "colors.asm"
.include "damage.asm"
.include "dpad.asm"
.include "main_menu.asm"
.importobj "../build/bundle.o"
.align 8
DPAD_TEXTURE:
.incbin("../../../resources/dpad32.bin")

.align 0x10
PAYLOAD_END:
.endarea //payload max memory

.close
