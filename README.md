# Hawk Language Scanner
This repository contains a **scanner** for the made-up language **Hawk**, developed as part of the Programming Language Fundamentals course at the **University of Houston Clear Lake**.

## Project Overview
The Hawk language scanner is designed to read source code written in Hawk, identify its lexemes and tokens, and check for basic syntax errors. This project focuses on building a **lexical analyzer** (lexer) and a **syntax analyzer** (parser), which together form the core of the scanner.

### Components
1. **Lexical Analyzer (Lexer):**
   - Reads the source code.
   - Identifies and categorizes lexemes (keywords, identifiers, operators, etc.).
   - Generates corresponding tokens.
2. **Syntax Analyzer (Parser):**
   - Ensures that the sequence of tokens follows Hawk's grammar rules.
   - Checks for syntax errors in the code.

## How to Use
1. Clone the repository:
   ```bash
   gh repo clone durkisneer1/Lexical-Analyzer
   ```
2. Run the `setup.py` file:
   ```bash
   python setup.py
   ```
3. Navigate to the `build` directory:
   ```bash
   cd build
   ```
4. Compile the generated build files:
   ```bash
   meson compile
   ```
5. Run `scanner.exe <filepath>` within a terminal to view trace output.

## Requirements
- C++ compiler (e.g., g++ or clang++)
- Meson and Ninja build systems installed through `pip` with Python
- Basic understanding of the Hawk language syntax (read example scripts)

## Project Structure
- `src/`: Contains the source files for the scanner.
- `include/`: Header files for the project.
- `test/`: Sample Hawk programs for testing the scanner.

## License
This project is for educational purposes and is licensed under the [MIT License](https://github.com/durkisneer1/Lexical-Analyzer/blob/main/LICENSE).
