# Simple C-to-Assembly Transpiler

> A minimal compiler developed to understand the fundamentals of code generation, register mapping, and translation from high-level syntax to low-level machine instructions.

## 📖 Overview

This project is a lightweight compiler built in **C** that translates a subset of C-like syntax into x86 Assembly instructions. It was developed to gain a deeper understanding of CPU instruction behavior, memory management, and the compilation pipeline.

The compiler takes source code containing arithmetic and logical operations and generates valid assembly code that maps variables to CPU registers (EAX, EBX, ECX, EDX).

## 🚀 Features

* **Arithmetic Operations:** Supports basic math instructions (`ADD`, `SUB`, `MUL`, `DIV`).
* **Logical & Control Flow:** Handles comparisons and jumps (`JMP`, conditional branches).
* **Register Mapping:** Implements a basic allocator to map variables to x86 registers (`EAX`, `EBX`, `ECX`, `EDX`).
* **Assignment handling:** Translates variable assignments into `MOV` instructions.
* **Minimal Syntax Support:** Optimized for educational purposes, focusing on core compilation concepts.

## 🛠️ Technologies

* **Language:** C (Standard C11)
* **Output:** x86 Assembly (Intel Syntax)
* **Build System:** Make

## 💻 Installation & Usage

### 1. Clone the repository
```bash
git clone [https://github.com/yourusername/simple-c-transpiler.git](https://github.com/yourusername/simple-c-transpiler.git)
cd simple-c-transpiler
```

### 2. Build the project
Use the included Makefile to compile the source code:
```bash
make
```
*Note: The binary will be generated in the project root.*

### 3. Run the transpiler
Provide a source file as input and define the output file:
```bash
./transpiler input.txt output.asm
```

### 4. Clean build files (Optional)
To remove object files and the executable:
```bash
make clean
```

## 📝 Example

**Input (input.txt):**
```c
int a = 10;
int b = 5;
int c = a + b;
```

**Output (output.asm):**
```asm
MOV EAX, 10      ; Load 10 into EAX (variable a)
MOV EBX, 5       ; Load 5 into EBX (variable b)
ADD EAX, EBX     ; Add EBX to EAX
MOV ECX, EAX     ; Store result in ECX (variable c)
```
