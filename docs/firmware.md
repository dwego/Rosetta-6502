# Firmware Development Guide for Rosetta-6502

This document explains how to build, assemble, link, and run custom 6502 firmware on the Rosetta-6502 virtual machine.  
It uses the `cc65` toolchain (`ca65` + `ld65`) and the VM’s configurable ROM layout.

---

# 1. Overview

Rosetta-6502 loads *raw* 16-bit 6502 binaries directly into the ROM region (`0xE000–0xFFFF`) and starts execution at the standard reset vector (`0xFFFC/FFFD`).  
This allows you to write:

- boot ROMs  
- BIOS routines  
- toy kernels  
- MMIO test programs  
- debugging payloads  

The workflow looks like this:

```

main_firmware.asm → ca65 → .o → ld65 (.cfg) → firmware.bin → Rosetta-6502 (--bin firmware.bin)

```

---

# 2. Installing cc65

macOS:

```bash
brew install cc65
```

Linux:

```bash
sudo apt install cc65
```

# 3. Minimal Firmware Example

Create `main_firmware.asm`:

```asm
.segment "CODE"

reset:
    sei         ; disable interrupts
    cld         ; clear decimal mode
    ldx #$FF
    txs         ; initialize stack pointer

    lda #$42
    sta $0200   ; absolute write (RAM), useful for VM testing
    brk         ; return control to emulator

.segment "VECTORS"
    .word reset       ; NMI
    .word reset       ; RESET
    .word reset       ; IRQ/BRK
```

## ⚠ Zero-page vs Absolute

The 6502 treats any address `< $0100` as “zero page”.
The assembler **will always optimize**:

```
sta $0040   → STA_ZP ($85)   (2 bytes)
```

Absolute addressing requires **≥ $0100**:

```
sta $0200   → STA_ABS ($8D) (3 bytes)
```

This is correct CPU behavior.

---

# 4. Linker Configuration (`firmware.cfg`)

Create `firmware.cfg`:

```cfg
MEMORY {
    ROM: start = $E000, size = $2000, file = %O;
}

SEGMENTS {
    CODE:    load = ROM, type = ro;
    VECTORS: load = ROM, type = ro, start = $FFFA;
}
```

This places:

* firmware code at `$E000`
* vectors at `$FFFA–FFFF`

---

# 5. Building the Firmware

```bash
ca65 main_firmware.asm -o main_firmware.o
ld65 main_firmware.o -o firmware.bin -C firmware.cfg
```

Check the output:

```bash
hexdump -C firmware.bin | head
```

Expected:

```
78 d8 a2 ff 9a a9 42 8d 00 02 ...
```

---

# 6. Running Firmware on Rosetta-6502

```bash
./main --bin firmware.bin
```

Debug output (if enabled) prints:

```
PC=E000 OP=78
PC=E001 OP=D8
PC=E002 OP=A2
PC=E004 OP=9A
PC=E005 OP=A9
PC=E007 OP=8D
PC=E00A OP=00
```

RAM viewer:

```
./main --bin firmware.bin --ram
```

---

# 7. Troubleshooting

### **STA turning into STA_ZP**

If you see `85 xx` instead of `8D xx xx`, you wrote to an address `< $0100`.
Choose a higher address (e.g. `$0200`).

### **ROM appears as zeros**

Make sure the firmware is linked to `$E000` using `firmware.cfg`.

### **VM loads wrong file**

Check current working directory:

```bash
pwd
ls -lah
```

