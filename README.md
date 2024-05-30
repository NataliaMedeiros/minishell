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


| Function		| Manual Page		| From lib			| Description
| :--			| :--				| :--				| :--
| **printf**	| `man 3 printf`	| `<stdio.h>`		| write output to stdout
| **malloc**	| `man malloc`		| `<stdlib.h>`		| allocate dynamic memory
| **free**		| `man 3 free`		| `<stdlib.h>`		| free dynamic memory
| **read**		| `man 2 read`		| `<unistd.h>`		| read from a file descriptor
| **write**		| `man 2 write`		| `<unistd.h>`		| write to a file descriptor
| **open**		| `man 2 open`		| `<fcntl.h>`		| open and possibly create a file
| **close**		| `man 2 open`		| `<unistd.h>`		| close a file descriptor
| **fork**		| `man fork`		| `<unistd.h>`		| create a child process
| **wait**		| `man wait`		| `<sys/wait.h>`	| wait for process to change state
| **waitpid**	| `man waitpid`		| `<sys/wait.h>`	| wait for process to change state
| **wait3**		| `man wait3`		| `<sys/wait.h>`	| (obsolete) wait for process to change state, BSD style
| **wait4**		| `man wait4`		| `<sys/wait.h>`	| (obsolete) wait for process to change state, BSD style
| **signal**	| `man signal`		| `<signal.h>`		| ANSI C signal handling
| **kill**		| `man 2 kill`		| `<signal.h>`		| send signal to a process
| **exit**		| `man exit`		| `<stdlib.h>`		| cause normal process termination
| **getcwd**	| `man getcwd`		| `<unistd.h>`		| get current working directory
| **chdir**		| `man chdir`		| `<unistd.h>`		| change working directory
| **stat**		| `man 2 stat`		| `<sys/stat.h>`	| get file status by pathname
| **lstat**		| `man lstat`		| `<sys/stat.h>`	| get file status by pathname (for symlinks)
| **fstat**		| `man fstat`		| `<sys/stat.h>`	| get file status by fd
| **execve**	| `man execve`		| `<unistd.h>`		| execute program
| **dup**		| `man dup`			| `<unistd.h>`		| duplicate a file descriptor
| **dup2**		| `man dup2`		| `<unistd.h>`		| duplicate a file descriptor
| **pipe**		| `man pipe`		| `<unistd.h>`		| create pipe
| **opendir**	| `man opendir`		| `<dirent.h>`		| open a directory
| **readdir**	| `man readdir`		| `<dirent.h>`		| read a directory
| **closedir**	| `man closedir`	| `<dirent.h>`		| close a directory
| **strerror**	| `man strerror`	| `<string.h>`		| return string describing error number
| **errno**		| `man errno`		| `<errno.h>`		| number of last error
| **termcap**	| `man termcap`, `man termios`		| `<term.h>`		| direct curses interface to the terminfo capability database

---

