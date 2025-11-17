
# Rosetta-6502 Dynamic Debugging System

Rosetta-6502 includes a flexible dynamic debugging module designed to make
instruction tracing, memory inspection, and CPU state visualization easy while
developing firmware or extending the emulator.

This guide covers:

- Debug levels and how they work
- How to enable debug output
- How instructions, CPU state, and memory operations are logged
- Where debug hooks exist in the emulator
- How to extend the system (breakpoints, stepping, disassembly)

---

# 1. Overview

The debug module lives in:

```

include/debug.h
src/debug/debug.c
```

It provides a structured and configurable way to inspect:

- Executed opcodes
- CPU registers per instruction
- Memory reads and writes
- Full execution trace (PC, flags, cycles)
- Event ordering and stack behavior

Debugging is **optional** and can be enabled or disabled at runtime.

---

# 2. Debug Levels

Debug output is controlled through the enum `DebugLevel`:

```c
typedef enum {
    DEBUG_OFF = 0,   // No output
    DEBUG_OPCODES,   // Show opcode fetches only
    DEBUG_CPU,       // Show CPU registers on each instruction
    DEBUG_TRACE,     // Combined opcode + CPU trace
    DEBUG_MEMORY     // Read/write memory logging
} DebugLevel;
```

You can switch debug level at any time by calling:

```c
debug_set_level(DEBUG_TRACE);
```

---

# 3. Enabling Debug in main.c

Inside `main.c`, you can choose which level to activate:

```c
#include "debug.h"

// ...

debug_set_level(DEBUG_TRACE);
// debug_set_level(DEBUG_MEMORY);
// debug_set_level(DEBUG_CPU);
// debug_set_level(DEBUG_OPCODES);
```

Leaving it as `DEBUG_OFF` produces no output.

---

# 4. What Each Level Shows

### DEBUG_OPCODES

Shows only instruction fetches:

```
[OP ] PC=E000 OP=78
[OP ] PC=E001 OP=D8
```

### DEBUG_CPU

Shows CPU registers each step:

```
[CPU] A=0C X=FF Y=02 SP=FF PC=E019  N:0 V:0 B:0 D:0 I:1 Z:0 C:0
```

### DEBUG_TRACE

Shows **both** opcode and CPU state:

```
[OP ] PC=E005 OP=A9
[CPU] A=00 X=FF Y=00 SP=FF PC=E006  N:0 V:0 B:0 D:0 I:1 Z:0 C:0
```

### DEBUG_MEMORY

Logs every RAM/ROM/MMIO read and write:

```
[READ ] 0200 => 34
[WRITE] 0201 <= 12
```

Useful for debugging load/store issues, ZP vs ABS behavior, and MMIO devices.

---

# 5. Where Debug Hooks Exist

Debug calls are placed at key points in the architecture:

### In opcode fetch:

```
debug_opcode(cpu->PC - 1, opcode);
debug_cpu_state(cpu);
```

This log appears **before** executing the instruction.

---

### In memory reads (cpu_read):

```c
debug_mem_read(addr, bus->data);
```

### In memory writes (cpu_write):

```c
debug_mem_write(addr, data);
```

These ensure full visibility into load/store operations, stack behavior, and MMIO accesses.

---

# 6. Source Code Layout

Debug header:

```
include/debug.h
```

Debug implementation:

```
src/debug/debug.c
```

Core areas that use debug hooks:

```
src/cpu/cpu_exec.c    ← instruction loop
src/bus/mem6502.c     ← memory read/write
src/main.c            ← enabling debug levels
```

---

# 7. Extending the Debug System

The debug module is intentionally simple and easy to extend.

## Breakpoints

You can add a breakpoint easily:

In `run_cpu_instruction`:

```c
if (cpu->PC == 0xE010) {
    printf("[BREAK] Hit breakpoint at E010\n");
    getchar(); // pause execution
}
```

Support for user-defined breakpoints can be added in `debug.h`.

---

## Single-step (manual stepping)

In `run_cpu_instruction`, add:

```c
getchar();
```

This pauses after each instruction until ENTER is pressed.

---

## Disassembler Output

You can generate human-readable mnemonics by:

* creating a `debug_disassemble()` function
* mapping opcodes to instruction names (you already have the tables)
* printing:

```c
PC, opcode, operands, mnemonic
```

This can go into:

```
src/debug/disassembler.c
```

---

## Watchpoints

You may extend memory debug to:

```c
if (addr == WATCH_ADDR) { ... }
```

Or generalize with a list of watched addresses.

---

# 8. Example Debug Session

With `DEBUG_TRACE` enabled:

```
Trying to load file: firmware.bin
Load complete!

[OP ] PC=E000 OP=78
[CPU] A=00 X=00 Y=00 SP=FD PC=E001  N:0 V:0 B:0 D:0 I:0 Z:0 C:0

[OP ] PC=E001 OP=D8
[CPU] A=00 X=00 Y=00 SP=FD PC=E002  N:0 V:0 B:0 D:0 I:1 Z:0 C:0

[OP ] PC=E007 OP=85
[CPU] A=12 X=FF Y=00 SP=FF PC=E008  N:0 V:0 B:0 D:0 I:1 Z:0 C:0

[READ ] 0010 => 12
[WRITE] 0201 <= 12
```

This provides full visibility into executed instructions and memory behavior.

---

# 9. Summary

The Rosetta-6502 debugger is:

* **modular**
* **easy to extend**
* **non-intrusive**
* **runtime-configurable**
* **suitable for firmware development**

It gives you everything you need to understand *exactly* what your firmware is doing — every cycle, every instruction, every memory access.

Future expansions (optional):

* full disassembler
* interactive monitor
* virtual breakpoints
* time-travel debugging
* memory diff viewer
