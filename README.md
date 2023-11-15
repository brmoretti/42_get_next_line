# get_next_line
<p align="center">
  <img src="https://game.42sp.org.br/static/assets/achievements/get_next_linem.png" alt="Achievement Image"><br>
</p>

## Overview

The `get_next_line` project at 42 school is a crucial challenge where students implement a function to read a line from a file descriptor. The goal is to create a function that reads one line at a time from a file, handles multiple file descriptors simultaneously, and manages dynamic memory allocation efficiently. The `get_next_line` function is essential for parsing and processing input from files or other sources line by line.

## Table of Contents

- [Getting Started](#getting-started)
- [Usage](#usage)
- [Project Structure](#project-structure)

## Getting Started

To begin working on the `get_next_line` project, follow these steps:

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/your_username/42_get_next_line.git
    ```

2. Navigate to the project directory:

    ```bash
    cd 42_get_next_line
    ```

3. Implement the `get_next_line` function according to the project requirements.

4. Build and test your function. You can set the BUFFER_SIZE variable. If omitted, the default is 80. To handle multiple file descriptors, compile with `get_next_line_bonus.c` instead of `get_next_line.c`.

    ```bash
    gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_main.c -o gnl
    ./gnl
    ```

    To handle multiple file descriptors:

    ```bash
    gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c your_main.c -o gnl_bonus
    ./gnl_bonus
    ```

## Usage

Once the `get_next_line` function is implemented and tested, you can integrate it into your projects by including the necessary header file and linking it during compilation.

```c
#include "get_next_line.h"
#include <stdio.h>

int  main(void)
{
    int      fd;
    char     *line;

    fd = open("example.txt", O_RDONLY);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s\n", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

## Project Structure

The project consists of a single source file (`get_next_line.c`) containing the implementation of the `get_next_line` function. The `get_next_line.h` header file declares the function prototype and includes any necessary libraries.

The `Makefile` or compilation script provided may facilitate building and testing the project. Ensure that dynamic memory allocation and file descriptor handling are appropriately managed in the implementation.
