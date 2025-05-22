# get_next_line

> A 42 school project to implement a function that reads a line from a file descriptor, handling memory and buffering manually.

## 📚 Description

The goal of this project is to write a function named `get_next_line` that reads from a file descriptor one line at a time, handling the internal buffer, partial reads, and memory allocation without using the standard `getline` function.

This function must:
- Return a full line ending with a newline character `\n`, if one exists.
- Be called repeatedly to get every line of a file until EOF.
- Work with different file descriptors, even interleaved.

This project teaches:
- Low-level file reading with `read()`
- Managing static variables
- Handling memory and buffers safely in C
- Edge cases such as EOF, empty lines, or read errors

## 🛠️ Usage

To use `get_next_line`, include the header in your project and compile it along with your source.

```c
#include "get_next_line.h"

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

## 📄 Function Prototype

```c
char *get_next_line(int fd);
```

- **fd**: The file descriptor to read from.
- **Returns**: A pointer to the next line, or `NULL` if EOF is reached or if `read()` returns an error.

## 🔍 How it works

- Uses `read()` to buffer input into memory.
- Appends and trims strings manually to extract lines.
- Handles static memory for multiple file descriptors.
- Does **not** use standard library functions like `getline()`.

> 🧠 You can read the official man page for `getline()` here:  
> https://man7.org/linux/man-pages/man3/getline.3.html

## ⚙️ Compilation

Use the following command to compile:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

You can define `BUFFER_SIZE` with `-D BUFFER_SIZE=n` to change how many bytes are read at once.

## 📁 File Structure

```
get_next_line/
├── get_next_line.c        # Main function logic
├── get_next_line.h        # Header file
├── get_next_line_utils.c  # Helper functions (e.g., string manipulation)
├── main.c                 # Optional test file
```

## ✅ Features

- Works with multiple file descriptors
- Handles large files and arbitrary buffer sizes
- No memory leaks (checked with Valgrind)

## 🚫 Limitations

- Doesn't support reading from stdin if `BUFFER_SIZE` is very small (can be optimized)
- Undefined behavior if `read()` is interrupted or returns null (e.g., closed file descriptor)

---

