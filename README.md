# C Header File Generator

This project is a C program that automatically generates a header (`.h`) file by scanning one or more C source files. It extracts valid function prototypes and writes them into a clean, organized header file.

---

## ✅ Features

- Reads `.c` files from either:
  - A **single file** input
  - A **full directory**
- Extracts only **valid function declarations**, skipping:
  - `static` functions
  - `main()` function
  - Inline function definitions (i.e. `{` on the same line)
  - Comments (`//`, `/* */`)
  - Strings, `printf`, and `return` lines (to avoid false matches)
- Sorts prototypes by **return type**
- Outputs a clean header file with proper **header guards**

---

## 🛠️ Usage

```bash
make
./generate_header <source_path_or_file> <output_header_file.h>
