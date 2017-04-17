# Get_Next_Line
### 42 - Project #3

The aim of this project is to code a function that returns a line, read from a file descriptor. In this case, a "line" is a succession of characters that end with ’\n’ (ascii code 0x0a) or with End Of File (EOF).

## Table of Contents
- [What is Get_Next_Line?](#what-is-get_next_line)
- [Bonus Part](#bonus-part)
- [How do I use this function?](#how-do-i-use-this-function)

### What is Get_Next_Line?

Get_Next_Line is a function that reads 1 single line from a file descriptor, and saves it to a string passed as as argument.
The function is prototyped as follow:

```C
int get_next_line(const int fd, char **line);
```

- The first parameter is the file descriptor that will be used to read.
- The second parameter is the address of a pointer to a character that will be used to save the line read from the file descriptor.
- The return value can be 1, 0 or -1 depending on whether a line has been read, when the reading has been completed, or if an error has happened respectively.
- Calling the function get_next_line in a loop will then allow you to read the an entire text file.

For more information, you can check out the [PDF].

### Bonus Part

The bonus part of this project consists in two things:

- Build the function using only one static variable
- To be able to handle multiple file descriptors

### How do I use this function

To use the following function you can run the following commands:
```
git clone --recursive https://github.com/giacomoguiulfo/get_next_line.git
cd get_next_line
make -C libft/
```
Then you would have to create a program with a main() function that receives files as arguments, include the "get_next_line.h" header file and call the get_next_line function. Here is a short example:
```C
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
  if (argc == 1) return (0);
  char *line;
  int fd = open(argv[1], O_RDONLY);
  while (get_next_line(fd, &line))
  {
    printf("%s\n", line);
    free(line);
  }
  return (0);
}
```
This program will output the entire file passed as argument to the stdout.

[PDF]: https://github.com/giacomoguiulfo/get_next_line/blob/master/get_next_line.en.pdf
