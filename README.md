# minishell
by [khirsig](https://github.com/khirsig) & [pweinstock](https://github.com/pweinstock)

The objective of this project is to create a simple shell. 
The requirements include:

- a prompt
- history of previous input
- launch executables (based on `PATH` variable, using relative or absolute path)
- single (`'`) and double (`"`) quotes to prevent the interpretation of meta-characters
- redirections:
  - input (`<`)
  - output (`>`)
  - here document (`<<`)
  - output append (`>>`)
- pipes (`|`) to connect commands
- expand environment variables (`$` followed by a sequence of characters)
- last exit status (`$?`)
- signal handling (`ctrl`+`C`, `ctrl`+`D`, `ctrl`+`\`)
- builtins:
  - `echo` with option `-n`
  - `cd` with relative or absolute path, `-` for `OLDPWD`, no argument for `HOME`
  - `pwd` without options
  - `export` without options
  - `unset` without options
  - `env` without options
  - `exit` with specific exit status

The behavior of bash is to be considered as a general reference.

## Allowed functions
```readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs```
## Approach
We split the handling of user input into four basic parts:

### 1. lexer 
The lexer is responsible for splitting the user input into basic tokens and representing them as individual elements in a list.
### 2. parser 
The parser takes the tokens produced by the lexer and interprets them, rearranging them into sublists.
### 3. expander 
The expander expands environment variables present in the input. It processes the input and replaces any environment variable references with their corresponding values.
### 4. executer 
The executor handles the execution of commands based on the processed input. It takes the parsed and expanded input and performs the necessary operations.
## How to use
```
git clone https://github.com/pweinstock/minishell.git
```
```
cd minishell
make
```
```
./minishell
```
