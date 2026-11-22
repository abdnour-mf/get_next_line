*This project has been created as part of the 42 curriculum by amfarrej.*

# Get Next Line

## Description

**Get Next Line (GNL)** is a 42 School project that consists of implementing a function capable of reading a file descriptor one line at a time.

The objective is to develop a function that returns a line whenever it is called, without reading the entire file at once. The function must preserve the remaining data between successive calls, allowing the reading process to continue exactly where it stopped.

This project introduces important concepts in C programming, particularly:

- Static variables and persistent data.
- File descriptors and the `read()` system call.
- Dynamic memory allocation and deallocation.
- String manipulation and memory management.
- Buffer-based reading and efficient data processing.

## Features

- Reads a file one line at a time.
- Supports file descriptors, including standard input.
- Handles lines ending with `\n`.
- Returns the final line even when it does not end with a newline.
- Preserves unread data between function calls.
- Handles different buffer sizes.
- Returns `NULL` when EOF is reached or an error occurs.

## Algorithm

The implementation follows a buffer-based reading approach using a static variable to preserve data between function calls.

The algorithm is divided into three main steps:

### 1. Read and Fill (`read_and_fill`)

- Allocates a temporary buffer of `BUFFER_SIZE + 1` bytes.
- Reads data from the file descriptor using `read()`.
- Appends the newly read data to the existing remaining content.
- Continues reading until a newline is encountered or EOF is reached.
- Handles allocation and reading errors.

### 2. Extract the Line (`extract_line`)

- Searches for the first newline character in the accumulated content.
- Calculates the length of the line to return.
- Allocates memory for the extracted line.
- Copies the line, including the newline character when present.

If EOF is reached without a newline, the remaining content is returned as the final line.

### 3. Update the Remaining Content (`update_remain`)

- Removes the portion of the content that has already been returned.
- Preserves everything after the extracted newline.
- Stores the remaining content for the next function call.

This ensures that unread data is never lost between successive calls.

### Why This Algorithm?

The use of a static variable allows the function to preserve its state between calls without requiring the caller to manage the remaining content manually.

Reading in chunks instead of loading the entire file into memory makes the implementation more memory-efficient and allows it to handle files of different sizes.

Separating reading, extraction, and updating into helper functions also makes the code easier to understand, maintain, and debug.

## Instructions

### Requirements

- A C compiler (`cc`).
- `make`.
- A Unix-like environment.

### Compilation

Clone the repository:

```bash
git clone <repository-url>
cd get_next_line
```

Compile the project using the Makefile:

```bash
make
```

Clean object files:

```bash
make clean
```

Remove object files and the compiled library:

```bash
make fclean
```

Recompile everything:

```bash
make re
```

### Compilation with BUFFER_SIZE

The project specification requires compilation with different buffer sizes.

Example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c
```

You can experiment with different values:

```bash
-D BUFFER_SIZE=1
-D BUFFER_SIZE=42
-D BUFFER_SIZE=9999
```

### Usage

Include the header:

```c
#include "get_next_line.h"
```

Example:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

Compile your test program together with the project source files.

## Project Structure

```text
get_next_line/
│
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── Makefile
└── README.md
```

## Testing

The implementation should be tested with different scenarios:

- Empty files.
- Files containing a single line.
- Files containing multiple lines.
- Lines ending with `\n`.
- Files without a trailing newline.
- Very long lines.
- Multiple consecutive newline characters.
- Different `BUFFER_SIZE` values.
- Reading from standard input.
- Invalid file descriptors.
- End-of-file handling.
- Memory allocation failures.

Memory management can also be checked using tools such as Valgrind.

## Resources

The following resources were useful for understanding the concepts involved in this project:

- [42 Get Next Line Subject](https://cdn.intra.42.fr/pdf/pdf/).
- [read() — Linux Manual](https://man7.org/linux/man-pages/man2/read.2.html).
- [malloc() — Linux Manual](https://man7.org/linux/man-pages/man3/malloc.3.html).
- [free() — Linux Manual](https://man7.org/linux/man-pages/man3/free.3.html).
- [Static Variables in C](https://en.cppreference.com/w/c/language/static.html).
- [File Descriptors — Linux Manual](https://man7.org/linux/man-pages/man2/open.2.html).

### AI Usage

AI tools were used as learning and debugging assistants throughout the project.

Their use included:

- Clarifying C programming concepts, particularly static variables, pointers, memory allocation, and file descriptors.
- Discussing possible approaches to the reading algorithm.
- Reviewing code and identifying potential logical errors.
- Understanding memory management and possible memory leaks.
- Identifying edge cases and suggesting testing scenarios.

The implementation and problem-solving process were approached as a learning exercise, with the objective of understanding the underlying concepts rather than relying on generated solutions.

## Author

**amfarrej**

42 Network — Computer Science Student