.segment "CODE"

reset:
    sei                 ; Disable interrupts
    cld                 ; Clear decimal mode

    ; Trigger a software interrupt
    brk

brk_handler:
    lda #'!'            ; Load ASCII '!'
    sta $D000           ; MMIO: PRINTCHAR

halt:
    jmp halt            ; Infinite loop (program halt)

.segment "VECTORS"
    .word reset         ; NMI vector
    .word reset         ; RESET vector
    .word brk_handler   ; IRQ / BRK vector