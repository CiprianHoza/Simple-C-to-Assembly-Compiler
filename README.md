# Simple C-to-Assembly Compiler

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

* **Language:** C
* **Output:** x86 Assembly (Intel Syntax)
* **Tools:** GCC, Make

## 💻 Installation & Usage

### 1. Clone the repository
```bash
git clone https://github.com/yourusername/simple-c-compiler.git
cd simple-c-compiler
```

### 2. Build the compiler
Compile the source code using GCC:
```bash
gcc main.c -o compiler
```

### 3. Run the compiler
Provide a source file as input and define the output file:
```bash
./compiler input.txt output.asm
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
