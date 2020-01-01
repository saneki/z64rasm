.n64
.relativeinclude on

.create "../roms/patched.z64", 0
.incbin "../roms/base.z64"

;==================================================================================================
; Constants
;==================================================================================================

.include "constants.asm"

;==================================================================================================
; Base game editing region
;==================================================================================================

.include "boot.asm"
.include "hacks.asm"
.include "hooks/colors.asm"
.include "hooks/dpad.asm"
.include "hooks/file_select.asm"
.include "hooks/general.asm"
.include "hooks/pause.asm"
.include "hooks/pushblock.asm"

;==================================================================================================
; New code region
;==================================================================================================

.headersize (G_PAYLOAD_ADDR - G_PAYLOAD_VROM)

.org G_PAYLOAD_ADDR
.area (G_PAYLOAD_SIZE - G_C_HEAP_SIZE) // Payload max memory
PAYLOAD_START:

.include "init.asm"
.include "every_frame.asm"
.include "colors.asm"
.include "damage.asm"
.include "dpad.asm"
.include "file_select.asm"
.include "pause.asm"
.include "pushblock.asm"
.include "underwater_ocarina.asm"
.importobj "../build/bundle.o"
.align 8
DPAD_TEXTURE:
.incbin("../../../resources/dpad32.bin")

.align 0x10
PAYLOAD_END:
.endarea // Payload max memory

.close
