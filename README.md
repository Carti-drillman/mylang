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

## Example Program

Here is an example of a simple program in `mylang`:

```plaintext
MOV num1 5          ; Set num1 to 5
MOV num2 10         ; Set num2 to 10
ADD num1 3          ; Add 3 to num1 (num1 = 5 + 3)
SUB num2 4          ; Subtract 4 from num2 (num2 = 10 - 4)
MUL num1 2          ; Multiply num1 by 2 (num1 = 8 * 2)
DIV num2 2          ; Divide num2 by 2 (num2 = 6 / 2)
PRINT num1          ; Print num1 (result: 16)
PRINT num2          ; Print num2 (result: 3)
