# Pipex

**A Unix pipeline implementation exploring low-level process communication and I/O redirection**

*Created as part of the 42 School curriculum by joesanto*

---

## Overview

Pipex is a system programming project that recreates Unix pipeline behavior from scratch. It demonstrates fundamental concepts in interprocess communication (IPC), file descriptor manipulation, and process management by implementing a command chaining mechanism similar to shell pipelines.

https://github.com/user-attachments/assets/6652888e-ace7-4d30-91da-1c4497317778

### Key Features

- Multi-command pipeline execution
- Input/output redirection
- Heredoc support
- Process isolation and communication via pipes
- Low-level file descriptor handling

---

## Building

Compile the project using the provided Makefile:
```bash
make
```

---

## Usage

### Standard Pipeline Mode
```bash
./pipex <infile> <cmd1> <cmd2> [cmd...n] <outfile>
```

**Example:**
```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

This mimics the shell command:
```bash
< input.txt grep hello | wc -l > output.txt
```

### Heredoc Mode
```bash
./pipex here_doc <DELIMITER> <cmd1> <cmd2> [cmd...n] <outfile>
```

**Example:**
```bash
./pipex here_doc EOF "grep pattern" "sort" output.txt
```

The `DELIMITER` specifies the string that marks the end of heredoc input.

---

## Implementation Details

### Architecture

Each command in the pipeline runs as a separate process. The implementation uses:

- **`pipe()`** system call to create communication channels between processes
- **`dup2()`** to redirect standard input/output to pipe file descriptors
- **`fork()`** and **`execve()`** for process creation and command execution

### Pipeline Flow

1. Create a pipe for each adjacent command pair
2. Fork a child process for each command
3. Redirect the child's stdin to read from the previous pipe
4. Redirect the child's stdout to write to the next pipe
5. Execute the command with `execve()`
6. Repeat until all commands in the chain are executed
7. Parent process waits for all children to complete

The first command reads from the input file, and the last command writes to the output file, with intermediate commands communicating purely through pipes.

---

## Learning Objectives

This project provides hands-on experience with:

- Unix process model and lifecycle
- File descriptor management and redirection
- Pipe-based IPC mechanisms
- System call interface (`fork`, `pipe`, `dup2`, `execve`, `waitpid`)
- Error handling in low-level operations
- Understanding shell pipeline internals

---

## Resources

- [Unix Pipes Explained](https://youtu.be/8Q9CPWuRC6o?si=ig8DTLLEi8LXJjce) - Video tutorial on pipe mechanics

---

## Author

**joesanto** - [42 School Porto]

---
