.segment "CODE"

reset:
    sei
    cld
    ldx #$FF
    txs

    lda #$42
    sta $0400   ; endereço não-zero-page


    brk

.segment "VECTORS"
    .word reset, reset, reset
