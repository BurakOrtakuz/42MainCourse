# 📚 Libft - Custom C Library

**Libft** is a custom C library that reimplements standard C functions, along with additional helper functions for linked lists and memory operations. This project was created as part of the 42 school curriculum.

## 📜 Functions Documentation

### 1. Character Classification & Conversion
| Function       | Description | Man Page |
|---------------|------------|---------|
| `ft_isalnum`  | Checks if a character is alphanumeric. | [isalnum(3)](https://man7.org/linux/man-pages/man3/isalnum.3.html) |
| `ft_isalpha`  | Checks if a character is alphabetic. | [isalpha(3)](https://man7.org/linux/man-pages/man3/isalpha.3.html) |
| `ft_isascii`  | Checks if a character is ASCII. | [isascii(3)](https://man7.org/linux/man-pages/man3/isascii.3.html) |
| `ft_isdigit`  | Checks if a character is a digit. | [isdigit(3)](https://man7.org/linux/man-pages/man3/isdigit.3.html) |
| `ft_isprint`  | Checks if a character is printable. | [isprint(3)](https://man7.org/linux/man-pages/man3/isprint.3.html) |
| `ft_tolower`  | Converts a character to lowercase. | [tolower(3)](https://man7.org/linux/man-pages/man3/tolower.3.html) |
| `ft_toupper`  | Converts a character to uppercase. | [toupper(3)](https://man7.org/linux/man-pages/man3/toupper.3.html) |

### 2. String Manipulation
| Function       | Description | Man Page |
|---------------|------------|---------|
| `ft_atoi`     | Converts a string to an integer. | [atoi(3)](https://man7.org/linux/man-pages/man3/atoi.3.html) |
| `ft_bzero`    | Zeroes a memory block. | [bzero(3)](https://man7.org/linux/man-pages/man3/bzero.3.html) |
| `ft_calloc`   | Allocates and zero-initializes memory. | [calloc(3)](https://man7.org/linux/man-pages/man3/calloc.3.html) |
| `ft_itoa`     | Converts an integer to a string. | - |
| `ft_memchr`   | Locates a byte in memory. | [memchr(3)](https://man7.org/linux/man-pages/man3/memchr.3.html) |
| `ft_memcmp`   | Compares memory blocks. | [memcmp(3)](https://man7.org/linux/man-pages/man3/memcmp.3.html) |
| `ft_memcpy`   | Copies memory. | [memcpy(3)](https://man7.org/linux/man-pages/man3/memcpy.3.html) |
| `ft_memmove`  | Safely copies overlapping memory. | [memmove(3)](https://man7.org/linux/man-pages/man3/memmove.3.html) |
| `ft_memset`   | Fills memory with a byte. | [memset(3)](https://man7.org/linux/man-pages/man3/memset.3.html) |
| `ft_split`    | Splits a string into an array of substrings. | - |
| `ft_strchr`   | Locates a character in a string. | [strchr(3)](https://man7.org/linux/man-pages/man3/strchr.3.html) |
| `ft_strdup`   | Duplicates a string. | [strdup(3)](https://man7.org/linux/man-pages/man3/strdup.3.html) |
| `ft_striteri` | Applies a function to each character in a string with index. | - |
| `ft_strjoin`  | Concatenates two strings. | - |
| `ft_strlcat`  | Safely concatenates strings (BSD-style). | [strlcat(3)](https://man.openbsd.org/strlcat.3) |
| `ft_strlcpy`  | Safely copies strings (BSD-style). | [strlcpy(3)](https://man.openbsd.org/strlcpy.3) |
| `ft_strlen`   | Computes the length of a string. | [strlen(3)](https://man7.org/linux/man-pages/man3/strlen.3.html) |
| `ft_strmapi`  | Applies a function to each character in a string. | - |
| `ft_strncmp`  | Compares two strings up to `n` bytes. | [strncmp(3)](https://man7.org/linux/man-pages/man3/strncmp.3.html) |
| `ft_strnstr`  | Locates a substring in a string. | [strnstr(3)](https://www.freebsd.org/cgi/man.cgi?query=strnstr) |
| `ft_strrchr`  | Locates the last occurrence of a character. | [strrchr(3)](https://man7.org/linux/man-pages/man3/strrchr.3.html) |
| `ft_strtrim`  | Trims characters from the start and end of a string. | - |
| `ft_substr`   | Extracts a substring. | - |

### 3. File Descriptor Output
| Function          | Description | Man Page |
|------------------|------------|---------|
| `ft_putchar_fd`  | Writes a character to a file descriptor. | - |
| `ft_putendl_fd`  | Writes a string + newline to a file descriptor. | - |
| `ft_putnbr_fd`   | Writes a number to a file descriptor. | - |
| `ft_putstr_fd`   | Writes a string to a file descriptor. | - |

### 4. Linked List Operations
| Function            | Description | Man Page |
|--------------------|------------|---------|
| `ft_lstadd_back`   | Adds a node to the end of a list. | - |
| `ft_lstadd_front`  | Adds a node to the start of a list. | - |
| `ft_lstclear`      | Deletes and frees a list. | - |
| `ft_lstdelone`     | Deletes a single node. | - |
| `ft_lstiter`       | Applies a function to each node. | - |
| `ft_lstlast`       | Returns the last node of a list. | - |
| `ft_lstmap`        | Creates a new modified list. | - |
| `ft_lstnew`        | Creates a new list node. | - |
| `ft_lstsize`       | Counts the number of nodes. | - |

---

## 🛠 Usage
1. **Compile the library:**
   ```bash
   make