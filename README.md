# Mini Compiler 🚀

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue?logo=cplusplus)
![FLEX](https://img.shields.io/badge/Lexical_Analysis-FLEX-orange)
![Bison](https://img.shields.io/badge/Parser-Bison-green)
![Build](https://img.shields.io/badge/Build-CMake%20%7C%20Make-lightgrey)

**A lightweight compiler built from scratch using C++17, FLEX, and Bison.**

Mini Compiler implements the core stages of a compiler, from lexical analysis and syntax parsing to semantic validation and intermediate code generation. It supports variable declarations, assignments, arithmetic expressions, conditional statements, and Three-Address Code (TAC) generation.

---

## 📑 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Compiler Architecture](#-compiler-architecture)
- [Supported Language](#-supported-language)
- [Prerequisites](#-prerequisites)
- [Installation and Build](#-installation-and-build)
- [Usage](#-usage)
- [Example](#-example)
- [Project Structure](#-project-structure)
- [Testing](#-testing)
- [Future Improvements](#-future-improvements)
- [Author](#-author)

---

## 🎯 Overview

Mini Compiler demonstrates how a compiler transforms source code into an intermediate representation through multiple processing stages.

The compiler processes a custom, C-like language and performs:

- Lexical analysis and tokenization
- LALR(1) syntax parsing
- Abstract Syntax Tree (AST) construction
- Scoped symbol table management
- Semantic validation
- Three-Address Code generation

The project emphasizes modular design, error handling, and separation between compiler stages.

## ✨ Features

| Component | Description |
|---|---|
| 🔍 Lexical Analysis | Tokenizes source code using FLEX |
| 🌳 Syntax Analysis | Parses grammar using Bison (LALR(1)) |
| 🧩 AST Construction | Builds an Abstract Syntax Tree |
| 📚 Symbol Table | Tracks variables and their scopes |
| ✅ Semantic Analysis | Validates declarations and variable usage |
| ⚙️ TAC Generation | Generates intermediate Three-Address Code |
| 🔢 Data Types | Supports integer variables |
| ➕ Arithmetic | Supports `+`, `-`, `*`, `/` and unary `-` |
| ⚖️ Comparisons | Supports `==`, `!=`, `<`, `<=`, `>`, `>=` |
| 🔀 Control Flow | Supports `if` and `if-else` statements |
| 🖨️ Output | Supports `print` statements |
| ❌ Error Reporting | Reports lexical, syntax, and semantic errors with line numbers |

## 🏗️ Compiler Architecture

```text
              Source Code (.mc)
                     |
                     v
          +----------------------+
          |  Lexical Analysis    |
          |       FLEX           |
          +----------------------+
                     |
                     v
          +----------------------+
          |  Syntax Analysis     |
          |       Bison          |
          +----------------------+
                     |
                     v
          +----------------------+
          |  AST Construction    |
          +----------------------+
                     |
                     v
          +----------------------+
          |  Semantic Analysis   |
          |  Scoped Symbol Table |
          +----------------------+
                     |
                     v
          +----------------------+
          |  TAC Generation      |
          +----------------------+
                     |
                     v
          +----------------------+
          | Intermediate Code    |
          +----------------------+
```

## 💻 Supported Language

### Variable Declarations

```c
int a;
int b;
int result;
```

### Arithmetic Expressions

```c
a = 10;
b = 20;
result = a + b * 3;
```

### Conditional Statements

```c
if (a < b) {
    print(a);
} else {
    print(b);
}
```

### Output Statements

```c
print(result);
```

**Supported operators**

- Arithmetic: `+`, `-`, `*`, `/`
- Unary: `-`
- Relational: `<`, `<=`, `>`, `>=`
- Equality: `==`, `!=`

Refer to the grammar and sample programs for the exact syntax supported by the implementation.

## 🛠️ Prerequisites

Make sure the following tools are installed:

- C++17-compatible compiler (GCC or Clang)
- FLEX
- Bison
- CMake (version 3.12 or later)
- Make

### Install dependencies on macOS

```bash
brew install flex bison cmake make
```

Ensure the required tools are available in your `PATH`.

## 🚀 Installation and Build

### 1. Clone the repository

```bash
git clone <YOUR_REPOSITORY_URL>
cd mini_compiler
```

Replace `<YOUR_REPOSITORY_URL>` with your actual GitHub repository URL.

### 2. Build using Make

```bash
make
```

### 3. Alternatively, build using CMake

```bash
cmake -S . -B build
cmake --build build
```

The executable is expected at `build/minic`.

## ▶️ Usage

### Generate Three-Address Code (TAC)

```bash
./build/minic examples/01_basic.mc
```

This runs the compiler on the sample program and displays its intermediate representation.

### Display the Abstract Syntax Tree (AST)

```bash
./build/minic --ast examples/01_basic.mc
```

This displays the Abstract Syntax Tree generated from the input program.

### Compile a Custom Program

Create a file named `program.mc`:

```c
int a;
int b;
int c;

a = 10;
b = 20;
c = a + b * 3;

print(c);
```

Run the compiler:

```bash
./build/minic program.mc
```

## 📋 Example

### Input

```c
a = 10;
b = 20;
c = a + b * 3;
```

### Generated Three-Address Code

```text
a = 10
b = 20
t0 = b * 3
t1 = a + t0
c = t1
```

Temporary variables such as `t0` and `t1` store intermediate computation results. Actual output depends on the compiler implementation.

## 📁 Project Structure

```text
mini_compiler/
├── examples/
│   └── 01_basic.mc
├── src/
├── include/
├── lexer.l
├── parser.y
├── CMakeLists.txt
├── Makefile
├── README.md
└── build/
    └── minic
```

*This is an illustrative structure. Update it to reflect your actual repository layout.*

## 🧪 Testing

Run the test suite:

```bash
make test
```

Manually test the compiler:

```bash
./build/minic examples/01_basic.mc
./build/minic --ast examples/01_basic.mc
```

Recommended test cases include:

- Valid variable declarations and assignments
- Arithmetic expressions and operator precedence
- Conditional statements
- Undeclared variables
- Duplicate declarations
- Invalid syntax
- Unsupported characters

## 🔮 Future Improvements

- Add loop constructs such as `while` and `for`
- Introduce additional data types and type checking
- Implement constant folding and code optimization
- Improve diagnostics with source-code context
- Generate assembly or machine code
- Expand unit and integration testing
- Add support for functions and procedure calls

## 🧰 Tech Stack

| Technology | Purpose |
|---|---|
| C++17 | Core compiler implementation |
| FLEX | Lexical analysis |
| Bison | Syntax analysis |
| CMake | Build configuration |
| Make | Build automation |

---

## 👨‍💻 Author

<div align="center">

### Sumit Kumar

**Mini Compiler — Built from scratch with C++17, FLEX, and Bison.**

Made with ❤️ by **Sumit Kumar**

</div>

---

⭐ If you find this project interesting, consider starring the repository!
