# Rosetta-6502 Firmware Builder
# Usage:
#   ./build.sh
#   ./build.sh <example-directory>

set -e  # stop on first error

# If an argument is provided, use it as the ASM directory.
# Otherwise, default to the current directory.
ASM_DIR="${1:-.}"

# Normalize path
ASM_DIR="$(cd "$ASM_DIR" && pwd)"

# Files inside ASM_DIR
ASM_FILE="$ASM_DIR/firmware.asm"
OBJ_FILE="$ASM_DIR/firmware.o"
BIN_FILE="$ASM_DIR/firmware.bin"
CFG_FILE="$ASM_DIR/none.cfg"
MMIO_CONFIG="$ASM_DIR/mmio.cfg"

# Root directory of Rosetta-6502 (parent of this script)
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$SCRIPT_DIR"

echo "=== Rosetta-6502 Firmware Builder ==="
echo "Firmware: $ASM_FILE"
echo "Output  : $BIN_FILE"
echo "Firmware CFG     : $CFG_FILE"
echo "Root    : $ROOT_DIR"
echo "MMIO CFG: $MMIO_CONFIG"
echo "--------------------------------------"

# Sanity checks
for file in "$ASM_FILE" "$CFG_FILE" "$MMIO_CONFIG"; do
    if [ ! -f "$file" ]; then
        echo "Error: file not found: $file"
        exit 1
    fi
done

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

# Run
if [ -f "$ROOT_DIR/main" ]; then
    echo "[4/4] Running on Rosetta-6502..."
    echo "--------------------------------------"
    "$ROOT_DIR/main" --bin "$BIN_FILE" --mmio "$MMIO_CONFIG"
else
    echo "[4/4] main executable not found. Run 'make' in project root first."
fi

