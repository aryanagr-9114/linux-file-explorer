# 📁 Linux File Explorer (Capstone Project)

### 👨‍💻 Author
**Aryan Agrawal**  
Email: [agarwalaryan9114@gmail.com](mailto:agarwalaryan9114@gmail.com)  
GitHub: [@aryanagr-9114](https://github.com/aryanagr-9114)

---

## 🧩 Overview
This project is a **console-based File Explorer** built in **C++17** using the `std::filesystem` library.  
It simulates Linux file operations such as `ls`, `cd`, `mkdir`, `cp`, and more — with colorful and emoji-rich output 💫.

The File Explorer allows you to navigate directories, create, copy, move, delete, search, and modify file permissions — all through a simple command-line interface.

---

## ⚙️ Features
✅ List files & directories (with color and emoji icons)  
✅ Create, copy, move, and delete files/folders  
✅ Recursive file search  
✅ View and modify file permissions  
✅ Simple Linux-style command experience  
✅ Works on **WSL (Ubuntu)** and **any Linux terminal**

---

## 🧱 Technologies Used
- **Language:** C++17  
- **Concepts:** Filesystem, Permissions, I/O Streams  
- **Tools:** WSL (Ubuntu), VS Code, Makefile  
- **Version Control:** Git & GitHub  

---

## 🖥️ Commands Supported

| Command | Description |
|----------|--------------|
| `ls` | List files and folders with emojis and colors |
| `cd <dir>` | Change directory |
| `pwd` | Show current directory path |
| `create-file <name>` | Create a new file |
| `mkdir <name>` | Create a new directory |
| `rm <path>` | Delete file or directory |
| `cp <src> <dst>` | Copy files or directories |
| `mv <src> <dst>` | Move or rename files or directories |
| `search <pattern>` | Search for files recursively |
| `viewperm <path>` | View file permissions |
| `chmod <octal> <path>` | Change file permissions |
| `help` | Show all commands |
| `exit` | Exit the explorer |

---

## 🧠 Example Usage

```bash
$ ./file-explorer
Simple Console File Explorer
Type 'help' for commands.
[/home/aryan/file-explorer] > mkdir demo
[/home/aryan/file-explorer] > cd demo
[/home/aryan/file-explorer/demo] > create-file hello.txt
[/home/aryan/file-explorer/demo] > ls
[FILE] 📄 hello.txt (0 bytes)
[/home/aryan/file-explorer/demo] > chmod 0755 hello.txt
[/home/aryan/file-explorer/demo] > viewperm hello.txt
Permissions: rwxr-xr-x
[/home/aryan/file-explorer/demo] > cd ..
[/home/aryan/file-explorer] > rm demo