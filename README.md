# 🐚 Minishell

A **minimalistic shell** inspired by **bash**, built in C! This project is part of the **42 School curriculum**, where we implement our own shell with fundamental UNIX features. 🚀

## 📝 What is Minishell?

Minishell is a small-scale **Unix shell** that mimics the behavior of Bash, implementing key functionalities of a command-line interpreter. It allows users to interact with the system by executing commands, handling input/output redirections, managing environment variables, and supporting pipes for command chaining.

The project focuses on understanding low-level **system calls**, **process control**, and **memory management**. Unlike a full-fledged shell like Bash or Zsh, Minishell is designed to provide a **lightweight yet functional** experience by implementing core features without unnecessary overhead.

### 🔍 Key Features & Objectives

✅ **Command Execution** – Supports running binaries from absolute, relative paths, and using the `$PATH` environment variable.  
✅ **Built-in Commands** – Implements `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit` without external binaries.  
✅ **Pipelines (`|`)** – Connects multiple commands where the output of one command becomes the input of another.  
✅ **Redirections (`<`, `>`, `>>`, `<<`)** – Handles input and output redirections including here-doc (`<<`).  
✅ **Environment Variable Expansion (`$VAR`)** – Supports substitution of environment variables like `$HOME`, `$USER`, etc.  
✅ **Exit Status (`$?`)** – Stores the exit status of the last executed command.  
✅ **Signal Handling** – Reacts to `Ctrl+C` (displays a new prompt), `Ctrl+D` (exits), and `Ctrl+\` (ignored like in Bash).  
✅ **History Support** – Saves and navigates through previously executed commands.   
✅ **Minimal Global Variables** – Uses at most **one global variable** for signal handling, ensuring structured memory management.  
✅ **Error Handling** – Properly manages invalid inputs, permission errors, and system call failures.  

## ⚡ Installation

Make sure you have `gcc` and `readline` installed on your system.

```bash
# Clone the repository
git clone https://github.com/Inzagini/minishell.git
cd minishell

# Compile the shell
make

# Run the shell
./minishell
```

## 🚀 Usage

Once inside `minishell`, you can run commands just like in a normal shell:

```bash
$ ls -l
$ echo "Hello, World!"
$ pwd
$ export MY_VAR=42
$ echo $MY_VAR
$ cat file.txt | grep keyword
$ ls > output.txt
```

### 🔧 Built-in Commands

| Command  | Description |
|----------|------------|
| `echo`   | Prints text to the terminal (supports `-n` option) |
| `cd`     | Changes the current directory |
| `pwd`    | Prints the current directory |
| `export` | Sets environment variables |
| `unset`  | Removes environment variables |
| `env`    | Prints all environment variables |
| `exit`   | Exits the shell |

## 📶 Signal Handling

| Shortcut  | Behavior |
|-----------|----------|
| `Ctrl + C` | Stops the current process and displays a new prompt |
| `Ctrl + D` | Exits the shell |
| `Ctrl + \` | Does nothing (ignored like in Bash) |

## 📂 Project Structure

```
minishell/
│── src/          # Source code files
│── include/      # Header files
│── Makefile      # Compilation rules
│── README.md
```

## 🛠 System Calls Used

- `fork()`, `execve()` → Process execution
- `pipe()`, `dup2()` → Handling pipes and redirections
- `waitpid()` → Managing child processes
- `signal()`, `sigaction()` → Handling signals

## 👨‍💻 Authors

- **Izagini** [GitHub Profile](https://github.com/Inzagini)
- **paul42b** [GitHub Profile](https://github.com/paul42b)

## 🌟 Acknowledgments

Thanks to **42 School** for this challenging project! 🎓
