.segment "CODE"

reset:
    sei
    cld

    ; ---- MMIO Print Test ----
    lda #'H'
    sta $D000

    lda #'I'
    sta $D000

    lda #10          ; newline
    sta $D000

    ; ---- VRAM Test ----
    lda #$42
    sta $D100        ; VRAM[0] = 0x42

    lda #$99
    sta $D101        ; VRAM[1] = 0x99

    ; ---- Keyboard Echo Test ----
    lda $D001        ; blocks until key (depends on handler)
    sta $0200        ; store in RAM
    sta $D000        ; echo to console

    brk

.segment "VECTORS"
    .word reset      ; NMI
    .word reset      ; RESET
    .word reset      ; IRQ/BRK
