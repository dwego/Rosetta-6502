#!/usr/bin/env bash

# Rosetta-6502 Firmware Builder
# Usage:
#   ./build.sh main_firmware.asm

set -e  # stop on first error

# Default firmware file
FIRMWARE=${1:-firmware.asm}

# Paths
ASM_DIR="$(dirname "$0")"
ASM_FILE="$ASM_DIR/$FIRMWARE"
OBJ_FILE="$ASM_DIR/firmware.o"
BIN_FILE="$ASM_DIR/firmware.bin"
CFG_FILE="$ASM_DIR/none.cfg"
MMIO_CONFIG="$ASM_DIR/mmio.cfg"

# Root directory of Rosetta-6502
ROOT_DIR="$(cd "$ASM_DIR/.." && pwd)"

echo "=== Rosetta-6502 Firmware Builder ==="
echo "Firmware: $ASM_FILE"
echo "Output  : $BIN_FILE"
echo "Firmware CFG     : $CFG_FILE"
echo "Root    : $ROOT_DIR"
echo "MMIO CFG: $MMIO_CONFIG"
echo "--------------------------------------"

# Check assembler/linker
if ! command -v ca65 >/dev/null 2>&1; then
    echo "Error: ca65 not found. Install cc65 first."
    exit 1
fi

if ! command -v ld65 >/dev/null 2>&1; then
    echo "Error: ld65 not found. Install cc65 first."
    exit 1
fi

# Assemble
echo "[1/4] Assembling..."
ca65 "$ASM_FILE" -o "$OBJ_FILE"

# Link
echo "[2/4] Linking..."
ld65 "$OBJ_FILE" -o "$BIN_FILE" -C "$CFG_FILE"

# Hexdump
echo "[3/4] Firmware Preview:"
hexdump -C "$BIN_FILE" | head

# Run optional (if main exists)
if [ -f "./main" ]; then
    echo "[4/4] Running on Rosetta-6502..."
    echo "--------------------------------------"
    "./main" --bin "$BIN_FILE" --mmio "$MMIO_CONFIG"
else
    echo "[4/4] main executable not found. Run 'make' in project root first."
fi
