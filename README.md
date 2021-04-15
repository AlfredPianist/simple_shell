# Holberton Simple Shell
This is a simple simulation of command line interpreter for linux using only, vi and emacs, compiled with gcc -Wall -Werror -Wextra -pedantic, gdb and valgrind

## Flowchart
![FLOWCHART] (./img/simple_shell.png)

## Setup
Compile the program using `gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`
and run the interpreter mode `./hsh` in addition, use `echo "ls" | ./hsh` or `./hsh < scripts_file` or `cat scripts_file | ./hsh` to use non-interactive mode

`$ cat scripts_file`
`ls`
`pwd`
`ls -la`

## Code Examples
To list the current directory.
`$ ./hsh`
` #cisfun$ ls`
` lslist.c              memory.c                README.md    test        builtins_2.c  ...`
` #cisfun$ exit`
or use
`$ echo "ls" | ./hsh`
` lslist.c              memory.c                README.md    test        builtins_2.c  ...`

or in general

`$ ./hsh`
` #cisfun$ [COMMAND] [ARGUMENTS]`
` ...`
` #cisfun$ exit`
-----------------------------
`$ echo "[COMMAND] [ARGUMENTS]" | ./hsh`
` ...`
-----------------------------
`$ cat scripts_file`
`[COMMAND] [ARGUMENTS]`
`[COMMAND] [ARGUMENTS]`
`...`
`$ cat scripts_file | ./hsh`
`....`
