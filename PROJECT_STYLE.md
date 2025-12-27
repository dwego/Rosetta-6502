# Project Coding Style & Structure Guidelines

This document describes the established coding style, file organization, and
testing patterns used in the **Rosetta-6502** project. Contributors should
follow these conventions to maintain consistency across the codebase.

---

## 1. Organization & File Layout

- Each CPU instruction has its own directory under ```src/cpu/Instructions/INSTR_NAME/``` containing a header file `instr.h`.

**Example:**  
The ORA instruction resides in: ``` src/cpu/Instructions/ORA/ora.h ```

- Common components (CPU, bus, memory) are defined in the `include/` directory,
such as: ```include/cpu6502.h```

- The main entry point of the program is: ```src/main.c```

- Documentation files live under the `docs/` directory.

---

## 2. Naming Conventions

- Header guards use uppercase with underscores:

```c
#ifndef ORA_H
#define ORA_H
````

* Macros and constants are uppercase with underscores and defined with one space
  after `#define`:

  ```c
  #define ROM_START 0xE000
  ```

* Functions and variables use descriptive names.

* Instruction functions use uppercase instruction names followed by the
  addressing mode:

  ```c
  LDA_ABS
  ORA_IM
  ```

* Pointer notation places the asterisk next to the variable name:

  ```c
  CPU6502 *cpu
  ```

---

## 3. Indentation & Formatting

* Indentation uses **two spaces per level**.

* Opening braces for functions and control structures are placed on a new line
  beneath the definition:

  ```c
  static inline void
  LDA_ABS (Bus6502 *bus, MEM6502 *memory, CPU6502 *cpu)
  {
    ...
  }
  ```

* Separate logical sections with blank lines for readability.

* Use `static inline` functions in instruction headers to encourage compiler
  inlining.

---

## 4. Comments & Documentation

* Precede each function or significant block with a multi-line comment
  explaining:

  * purpose
  * parameters
  * side effects

* Use single-line `//` comments for short explanations inside functions.

* When implementing instructions, document:

  * supported addressing modes
  * timing behavior
  * cycle penalties (e.g., page crossings)

  Follow the existing style used in `ora.h`.

---

## 5. Coding Practices

* **C Standard**
  Code is written in **C11**. Avoid compiler-specific extensions.

* **Clarity over micro-optimisations**
  Prioritise readability and maintainability. Use descriptive variable names and
  break complex expressions into smaller steps.

* **Status Flags Handling**
  Instructions that affect CPU flags should use a dedicated helper function:

  ```c
  LDASetStatus(...)
  ```

  Call it after updating the target register.

* **Memory Access**
  Use the provided helpers to simulate correct CPU behavior:

  * `FetchByte`
  * `FetchWord`
  * `cpu_read`
  * `spend_cycle`
  * `spend_cycles`

---

## 6. Testing Pattern

* Tests live under the `tests/` directory.

* Each instruction group has:

  * a helper implementation file (e.g., `ld_helpers.c`)
  * a corresponding header (e.g., `test_ld.h`)

* Tests use **Unity** for assertions.

* Test cases are defined as arrays (e.g., positive, zero, negative values) and
  executed in loops.

* Use `load_and_run` to execute instruction byte sequences with the expected
  number of cycles.

* Validate register values and flags using Unity macros such as:

  ```c
  TEST_ASSERT_EQUAL_MESSAGE
  ```

* After each test case:

  * call `resetCPU`
  * clear any modified registers

---

## 7. Project Build & Tooling

* The project builds on **macOS and Linux** using:

  * `clang` or any C11-compatible compiler
  * `make`

* Running `make` in the repository root produces the `main` executable.

* Tests are built by running `make` inside the `tests/` directory.

---

## 8. Communication & Collaboration

* Ensure all new code adheres to this document before submitting a pull request.

* Discuss significant changes via issues or pull requests to align with project
  maintainers.

* When in doubt:

  * follow existing patterns in the codebase
  * prioritise consistency

---

Adhering to this style guide helps maintain a clean, readable, and maintainable
codebase. Thank you for your contributions.
