.n64
.relativeinclude on

.create "../roms/patched.z64", 0
.incbin "../roms/base.z64"

;==================================================================================================
; Constants
;==================================================================================================

.include "constants.asm"
.include "dmadata.asm"

;==================================================================================================
; RAM translation for "code" (file 31)
;==================================================================================================

.headersize (G_CODE_RAM - G_CODE_FILE) // ROM != VROM for all tools

;==================================================================================================
; Base game editing region
;==================================================================================================

.include "boot.asm"
.include "hacks.asm"
.include "hooks/colors.asm"
.include "hooks/dpad.asm"
.include "hooks/file_select.asm"
.include "hooks/general.asm"
.include "hooks/items.asm"
.include "hooks/misc.asm"
.include "hooks/pause.asm"
.include "hooks/pushblock.asm"
.include "hooks/quest_items.asm"
.include "hooks/rooms.asm"

;==================================================================================================
; New code region
;==================================================================================================

.headersize (G_PAYLOAD_ADDR - G_PAYLOAD_VROM)

.org G_PAYLOAD_ADDR
.area (G_PAYLOAD_SIZE - G_C_HEAP_SIZE) // Payload max memory
PAYLOAD_START:

.include "init.asm"
.include "colors.asm"
.include "damage.asm"
.include "dpad.asm"
.include "file_select.asm"
.include "items.asm"
.include "misc.asm"
.include "pause.asm"
.include "player_actor.asm"
.include "pushblock.asm"
.include "quest_items.asm"
.include "rooms.asm"
.include "song_of_time.asm"
.importobj "../build/bundle.o"
.align 8
DPAD_TEXTURE:
.incbin("../../../resources/dpad32.bin")

.align 0x10
PAYLOAD_END:
.endarea // Payload max memory

.close
