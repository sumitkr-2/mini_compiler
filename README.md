# Mini Compiler

A complete mini compiler implemented in C++17 using FLEX for lexical analysis and Bison for syntax analysis.

## Features
- Lexical analysis using FLEX
- Syntax analysis using Bison (LALR(1))
- Abstract Syntax Tree (AST) construction
- Scoped symbol table and semantic validation
- Intermediate Three-Address Code (TAC) generation
- Integer variables, declarations, assignments, arithmetic (`+`, `-`, `*`, `/`, unary `-`), relational comparisons (`==`, `!=`, `<`, `<=`, `>`, `>=`)
- `print` statements and `if`/`else` control flow
- Error reporting with line numbers for lexical, syntax, and semantic errors

## Prerequisites
- C++17 compatible compiler (`g++` or `clang++`)
- `flex`
- `bison`
- `cmake` (>= 3.12) and `make`

## Build
```bash
make
```
Or with CMake directly:
```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

## Running
Generate Three-Address Code (TAC):
```bash
./build/minic examples/01_basic.mc
```

Display Abstract Syntax Tree (AST):
```bash
./build/minic --ast examples/01_basic.mc
```

## Running Tests
```bash
make test
```
