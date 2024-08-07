# minishell

To starting developing the minishell we could break it in two step:
- Parsing
- Execution

## Parsing
The parser process takes the sequence of tokens produced by the lexer and processes them according to the grammatical rules of the language.
- Lexal analyses
	As the first phase od a compiler or intepreter, the lexical analyser (lexer) is responsible for reading the input and converting it into a sequence of tokens.

- Tokens
	Tokens are the smallest units of meaningful data in your input. They are sequences of characters that represent fundamental elements of the language, such as keywords, identifiers, operators, literals, and punctuation.

Example:
 Consider the following command line:
	cat file.txt | grep "search string" > output.txt

The lexer will break it into the following tokens:
	- 'cat'
	- 'file.txt'
	- '|'
	- 'grep'
	- '"search string"'
	- '>'
	- 'output.txt'

Command Table
To store these tokens, we use a command table, which organizes all these tokens into a list of simple commands. Each simple command in the command table contains the command itself and its arguments

### Functions allowed on this project

| Function		| Lib			| Description


| Function		| From lib			| Description
| :--			| :--				| :--
| **printf** 	| `<stdio.h>`		| write output to stdout
| **readline**	| <readline/readline.h><readline/history.h> | get a line from a user with editing
| **rl_clear_history** |
| **rl_on_new_line** |
| **rl_replace_line** |

,
, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,≈
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
---

