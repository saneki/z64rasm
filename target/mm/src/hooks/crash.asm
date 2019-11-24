;==================================================================================================
; Induce a Crash on Pause Menu
;==================================================================================================
;
; This is used to induce a crash when using the pause menu. It is primarily intended for debugging
; on console to get a (working) crash debugger.
; Replaces:
;   lw      s1, 0x0018 (sp)
.orga 0xBF269C ; In memory: 0x8075D54C
    sw      s1, 0x0000 (r0)
