# 🐚 Minishell

A **minimalistic shell** inspired by **bash**, built in C! This project is part of the **42 School curriculum**, where we implement our own shell with fundamental UNIX features. 🚀

## ✨ Features

✅ Custom shell prompt  
✅ Command execution with **PATH resolution**  
✅ **Pipes ( | )** to chain commands  
✅ **Redirections** ( >, >>, <, << )  
✅ Environment variable handling (e.g., `$HOME`, `$USER`)  
✅ **Signal handling** (Ctrl + C, Ctrl + D, Ctrl + \)  
✅ Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`  

## ⚡ Installation

Make sure you have `gcc` and `readline` installed on your system.

```bash
# Clone the repository
git clone https://github.com/yourusername/minishell.git
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

## 🎯 Signal Handling

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
│── README.md     # This file!
```

## 🛠 System Calls Used

- `fork()`, `execve()` → Process execution
- `pipe()`, `dup2()` → Handling pipes and redirections
- `waitpid()` → Managing child processes
- `signal()`, `sigaction()` → Handling signals

## 👨‍💻 Authors

- **Your Name** - [GitHub Profile](https://github.com/yourusername)

## 🌟 Acknowledgments

Thanks to **42 School** for this challenging project! 🎓
