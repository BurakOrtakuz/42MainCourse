# ft_printf

> A 42 school project to reimplement the standard C `printf` function with limited features and full manual formatting.

## 📚 Description

The `ft_printf` project is a custom implementation of the standard C library's `printf` function. It replicates formatted output to the standard output using a restricted subset of specifiers.

This project teaches:
- Variadic functions in C (`stdarg.h`)
- Handling and parsing format strings
- Converting different data types to string
- Managing output and memory manually

## 🛠️ Usage

Include `ft_printf.h` in your code and link your compiled files:

```c
#include "ft_printf.h"

int main(void)
{
    int len;

    len = ft_printf("Hello, %s! The answer is %d\n", "world", 42);
    ft_printf("Printed %d characters.\n", len);
    return 0;
}
```

## 📄 Function Prototype

```c
int ft_printf(const char *format, ...);
```

- **format**: A C string that contains the text to be written, optionally including format specifiers.
- **...**: A variable number of arguments to format and print.
- **Returns**: The total number of characters printed.

## ✅ Supported Conversions

The following format specifiers are supported:

| Specifier | Description              |
|-----------|--------------------------|
| `%c`      | Character                |
| `%s`      | String                   |
| `%p`      | Pointer address          |
| `%d`      | Signed decimal integer   |
| `%i`      | Signed decimal integer   |
| `%u`      | Unsigned decimal integer |
| `%x`      | Hexadecimal (lowercase)  |
| `%X`      | Hexadecimal (uppercase)  |
| `%%`      | A literal percent sign   |

## 🔍 How it works

- Uses `va_start`, `va_arg`, and `va_end` to handle variable arguments.
- Parses the format string to identify and process specifiers.
- Converts data types to strings using custom functions.
- Outputs characters using `write()` for maximum control.

## ⚙️ Compilation

Use the following command to compile:

```bash
gcc -Wall -Wextra -Werror ft_printf.c ft_printf_utils.c main.c
```

You may need to adjust the file list depending on how you've split your code.

## 📁 File Structure

```
ft_printf/
├── ft_printf.c        # Main printf implementation
├── ft_printf.h        # Header file
├── ft_printf_utils.c  # Helper functions (e.g., integer/hex conversion)
├── main.c             # Optional test file
```

## ✅ Features

- Accurate formatted output for supported specifiers
- Compatible with standard output via `write()`
- Returns correct character count
- Handles null strings and pointer values safely

## 🚫 Limitations

- Does not support width, precision, or flags (e.g. `%-5s`, `%.2f`)
- Limited to specifiers listed above

---
