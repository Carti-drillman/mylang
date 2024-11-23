# MyLang Interpreter

MyLang is a simple, custom programming language and interpreter written in C. It supports basic arithmetic operations, variable assignments, and control flow statements. This project serves as a learning tool to understand how interpreters work and how custom programming languages can be designed.

## Features

- **Basic Arithmetic**: Supports addition, subtraction, multiplication, division, and modulo operations.
- **Variables**: Allows variable assignment and retrieval.
- **Control Flow**: Conditional jumps based on variable values.
- **Stack Operations**: Includes basic stack operations like `PUSH` and `POP`.
- **Input/Output**: Basic I/O operations like printing and user input.

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/mylang.git
    cd mylang
    ```

2. Compile the project using `gcc` or any other C compiler:
    ```bash
    gcc -o mylang src/*.c
    ```

3. Run the interpreter with an example program:
    ```bash
    ./mylang examples/hello.mylang
    ```

## Example Program (Assembly-like)

Here is an example of a simple program in assembly-like pseudocode:

```assembly
MOV R1, 5          ; Set R1 to 5
MOV R2, 10         ; Set R2 to 10
ADD R1, 3          ; Add 3 to R1 (R1 = 5 + 3)
SUB R2, 4          ; Subtract 4 from R2 (R2 = 10 - 4)
MUL R1, 2          ; Multiply R1 by 2 (R1 = 8 * 2)
DIV R2, 2          ; Divide R2 by 2 (R2 = 6 / 2)
PRINT R1           ; Print R1 (result: 16)
PRINT R2           ; Print R2 (result: 3)
