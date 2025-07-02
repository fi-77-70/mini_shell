## ABOUT

**The Challenge**

Minishell was a key individual project for me at 42 Porto. The goal was to build a simplified Bash shell from scratch, implementing core features like prompt display, command history, executable launching, quoting, redirections, pipes, environment variables, signals, and built-in commands.

**Understanding Bash**

To approach this, I broke down Bash into its core components — lexer, parser, expander, and executor — tackling each step carefully to ensure a faithful and complete implementation.

<br>

## Implementation

**Lexer**<br>
Tokenizes user input into a linked list, identifying words and special characters for parsing.

**Parser**<br>
Groups tokens into commands, handles redirections, and marks built-in commands, creating structured data ready for execution.

**Builtins**<br>
Implemented built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`) using function pointers linked to command structures for efficient execution.

**Executor**<br>
Manages command execution, including multiple commands connected via pipes and process management.

**Expander**<br>
Replaces variables with their values and processes heredocs before execution.

**Heredoc**<br>
Handled by writing input to temporary files, mimicking Bash’s behavior simply and reliably.

**Single and Multiple Commands**<br>
Handles both single commands and pipelines, creating child processes and managing inter-process communication.

**Reset**<br>
Cleans up and resets program state between commands to ensure stable operation.

<br>

## Challenges and Takeaways

The toughest part was handling edge cases, which required extensive debugging and testing. Working alone helped me deeply understand system-level programming concepts. The iterative feedback process refined the project until its successful completion. Minishell represents my commitment to mastering low-level programming and building a functional shell.

<br>

#### MAKEFILE COMMANDS
`make` or `make all` - Compile program **mandatory** files.

`make clean` - Delete all .o (object files) files.

`make fclean` - Delete all .o (object file) and .a (executable) files.

`make re` - Use rules `fclean` + `all`.

<br>

## NORMINETTE
At 42 School, projects are generally expected to adhere to the Norm, the school's coding standard:

```
- No for, do while, switch, case or goto are allowed
- No more than 25 lines per function and 5 functions per file
- No assigns and declarations in the same line (unless static)
- No more than 5 variables in 1 function
... 
```

* [Norminette](https://github.com/42School/norminette) - Tool by 42, to respect the code norm. `GitHub`
* [42 Header](https://github.com/42Paris/42header) - 42 header for Vim. `GitHub`
