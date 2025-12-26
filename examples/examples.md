# Examples – Rosetta-6502

This directory contains self-contained examples for the Rosetta-6502 emulator.
Each example includes a small 6502 firmware, along with its linker and MMIO
configuration, demonstrating how to run code on the emulator.

---

## Directory Structure

Each example must follow this structure:

```

examples/ <example-name>/
firmware.asm   # 6502 firmware source
mmio.cfg       # MMIO device configuration
none.cfg       # Memory/linker configuration

```

---

## Running an Example

To run an example, invoke `build.sh` and pass the example directory as the
argument:

```bash
./build.sh examples/00-minimal-hello
```

If you are already inside the `examples` directory:

```bash
../build.sh 00-minimal-hello
```

The build script will automatically:

1. Assemble `firmware.asm`
2. Link using `none.cfg`
3. Load the MMIO configuration from `mmio.cfg`
4. Execute the firmware on the Rosetta-6502 emulator

---

## What the Examples Demonstrate

Depending on the example, you may see:

* MMIO output via `PRINTCHAR`
* Keyboard input via `KEYBOARD`
* Writes to VRAM-mapped memory regions
* Reset vectors and basic firmware flow
* Direct interaction with emulated hardware

---

## Creating New Examples

To create a new example:

1. Copy an existing example directory
2. Rename the directory
3. Modify `firmware.asm`, `mmio.cfg`, and `none.cfg`
4. Run it using:

```bash
./build.sh examples/<new-example>
```

