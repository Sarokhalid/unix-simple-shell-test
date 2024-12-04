## Shell Program Documentation

### Authors

This project is a collaborative effort by the following individuals:

## Sara Khalid Mustafa
- Email: saramustafa1842002@gmail.com
## Yousra Hassan Omer Hassan
- Email: Yousrah912@gmail.com
## Amna Hussien Adam Ahmed
- Email: amnahussin88@gmail.com
## Project Details
- Project Name: Unix Simple Shell
- Project Description: A simple shell project in C89 
## Rawan Ezz Eldeen Sayed Mohammed 
 - Email: rwnhr5152@gmail.com

### Introduction

The shell program is a command-line interpreter that allows users to execute commands and manage a command history. This program is implemented in C and provides various functionalities like executing commands, changing directories, and maintaining a command history.                      

------------------------------------------------------

Features
--------

-   Implements a subset of sh functionality
-   Supports most basic shell commands like ls, echo, cat, cd , quit etc.
-   Handles semicolon separated commands
-   Supports comments using #
-   Includes custom implementations of several C standard library functions.
-   Reads and executes commands from files
-   Handles Ctrl-D, Ctrl-C (SIGINT) and Ctrl-Z (SIGTSTP) signals
-   Saves command history to a file
-   Prints prompts and errors to stderr

Usage
-----

```
git clone https://github.com/Sarokhalid/simple_shell.git
cd simple_shell
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell
./shell

```

Type commands and press Enter to execute. Use Ctrl-C or Ctrl-Z to handle signals.

Examples
--------

```
$ ./shell
$ ls
file1 file2
$ cat file1
Hello World!
```

### Code Structure:

#### Description of each function in this code accourding to C files:

Shell Header File (shell.h)
===============================

Overview
--------

This header file, defines data structures, function prototypes, and constants used in a C program representing a basic shell.

Included Libraries
------------------

The header file includes several standard C libraries, each of which plays a crucial role in the functionality of the shell program:

-   `stdio.h`: For standard input/output operations.
-   `stdlib.h`: For memory allocation and deallocation functions.
-   `string.h`: For string manipulation functions.
-   `signal.h`: For handling signals such as SIGINT and SIGTSTP.
-   `sys/types.h`: For data types used in system calls.
-   `sys/wait.h`: For process and status information.
-   `fcntl.h`: For file control options (used for working with files).
-   `unistd.h`: For POSIX system calls and constants.
-   `limits.h`: For platform-independent constant values.
-   `pwd.h`: For retrieving user information.
-   `errno.h`: For handling errors and reporting error codes.

Constants
---------

The header file defines several constants, which are used throughout the shell program to control its behavior and maintain specific limits:

-   `MAX_CMD_LEN`: Specifies the maximum length of a command that the shell can handle.
-   `HISTORY_COUNT`: Defines the maximum number of commands to store in the command history.
-   `HISTORY_FILE`: Specifies the name of the history file where command history is stored.

Data Structures
---------------

Two main data structures are defined in the header file to manage the command history:

1.  `Node` Structure:

    -   A structure representing a node in a linked list. Each node stores a command and a pointer to the next node.
2.  `shell_data` Structure:

    -   A structure that holds the head of the linked list, representing the command history.

Function Prototypes
-------------------

The header file declares various function prototypes, indicating the functions' names, parameters, and their purposes. These functions are the building blocks of the shell program:

-   Signal Handling Functions:

    -   `handle_sigint`: Handles the SIGINT signal (Ctrl+C).
    -   `handle_sigtstp`: Handles the SIGTSTP signal (Ctrl+Z).
    -   `handle_signals`: Sets up signal handlers for SIGINT and SIGTSTP.
-   Command History Management Functions:

    -   `insert_cmd`: Inserts a command into the command history.
    -   `clear_history`: Clears the entire command history.
    -   `write_history`: Writes the command history to a file.
    -   `read_history`: Reads the command history from a file.
-   Command Execution Functions:

    -   `execute_cd_command`: Handles the "cd" command for changing directories.
    -   `execute_other_command`: Executes a command in a child process.
    -   `execute_command_in_path`: Executes a command by searching in directories listed in the PATH environment variable.
    -   `print_error_message`: Prints an error message when a command is not found.
    -   `execute_cmd`: Parses and executes a given command.
-   File and Input/Output Functions:

    -   `check_history_file`: Checks the existence of the history file and creates it if it doesn't exist.
    -   `execute_commands_from_file`: Reads and executes commands from files.
    -   `execute_commands_interactively`: Handles interactive command execution.
-   User Interface Functions:

    -   `print_prompt`: Displays the shell prompt.
    -   `read_command`: Reads a command from the user.
    -   `check_command_length`: Checks if a command exceeds the maximum allowed length.


I - Signal handling (signal_handling.c):
==========================================
1.  **handle_sigint**:

    -   Description: Handles the SIGINT signal, which is triggered when the user presses Ctrl+C. It simply writes a newline and the shell prompt to stdout.
    -   Parameters:
        -   `int signum` - The signal number.
    -   Return Value: None.
2.  **handle_sigtstp**:

    -   Description: Handles the SIGTSTP signal, which is triggered when the user presses Ctrl+Z. It writes a newline to stdout.
    -   Parameters:
        -   `int signum` - The signal number.
    -   Return Value: None.
3. **handle_signals**:

    -   Description: Sets up signal handlers for SIGINT (Ctrl+C) and SIGTSTP (Ctrl+Z). These handlers control the behavior of the shell when these signals are received.
    -   Parameters: None.
    -   Return Value: None.

II - Command history (command_history.c):
=========================================
1.  **insert_cmd**:

    -   Description: Inserts a command into the command history data structure. If the history count exceeds the specified limit, the oldest command is removed.
    -   Parameters:
        -   `shell_data *data` - A pointer to the shell data structure.
        -   `const char *cmd` - The command to be inserted.
    -   Return Value: None.
2.  **clear_history**:

    -   Description: Clears the entire command history by freeing the memory associated with each command node.
    -   Parameters:
        -   `shell_data *data` - A pointer to the shell data structure.
    -   Return Value: None.
3.  **write_history**:

    -   Description: Writes the command history to a file specified by HISTORY_FILE. It opens the file, iterates through the history, and writes each command followed by a newline character.
    -   Parameters:
        -   `shell_data *data` - A pointer to the shell data structure.
    -   Return Value: None.
4.  **read_history**:

    -   Description: Reads the command history from a file specified by HISTORY_FILE. It opens the file, reads each line (command), and inserts it into the command history.
    -   Parameters:
        -   `shell_data *data` - A pointer to the shell data structure.
    -   Return Value: None.
5. **check_history_file**:

    -   Description: Checks if the history file exists. If it doesn't, it creates the file. It is responsible for managing the history file for storing command history.
    -   Parameters: None.
    -   Return Value: None.

III - Command execution (command_execution.c):
=============================================
1.  **execute_cd_command**:

    -   Description: Handles the "cd" command, which is used to change directories. It checks if an argument is provided and attempts to change the directory using the chdir function.
    -   Parameters:
        -   `char *args[]` - An array of command arguments.
    -   Return Value: None.
2. **execute_command_in_path**:

    -   Description: Attempts to execute a command by searching for its executable in directories listed in the PATH environment variable. If found, it calls `execve` to execute the command.
    -   Parameters:
        -   `char *args[]` - An array of command arguments.
        -   `char *error_message` - A buffer for storing error messages.
        -   `int *length` - A pointer to the length of the error message.
    -   Return Value: None.
3. **execute_other_command**:

    -   Description: Executes a command in a child process. It duplicates the standard output and tries to execute the command directly. If the direct execution fails, it searches for the command in directories listed in the PATH environment variable and attempts to execute it there.
    -   Parameters:
        -   `char *args[]` - An array of command arguments.
        -   `char *argv[]` - An array of command arguments (used for error messages).
    -   Return Value: None.
4. **execute_cmd**:

    -   Description: Parses and executes a given command, including handling the "cd" command and other commands. It also updates the command history.
    -   Parameters:
        -   `const char *cmd` - The command to execute.
        -   `char *argv[]` - An array of command arguments.
    -   Return Value: None.

IV - Interactive shell operations (interactive_shell_operations.c):
==================================================================
1. **print_prompt**:

    -   Description: Prints the shell prompt, which typically includes the username and current working directory.
    -   Parameters:
        -   `char *username` - The username of the current user.
        -   `char *cwd` - The current working directory.
    -   Return Value: None.
2. **read_command**:

    -   Description: Reads a command from the user. It uses the `getline` function to read input from the user.
    -   Parameters:
        -   `char **cmd` - A pointer to the buffer for storing the command.
        -   `size_t *len` - A pointer to the length of the command.
    -   Return Value: None.
3. **check_command_length**:

    -   Description: Checks if a command exceeds the maximum allowed length and prints an error message if it does.
    -   Parameters:
        -   `char *cmd` - The command to check.
    -   Return Value: None.
4. **execute_commands_interactively**:

    -   Description: Handles interactive command execution for the shell. It continuously reads user input, checks for commands like "exit" or "quit" to exit the shell, and executes other commands.
    -   Parameters:
        -   `char *cmd` - A buffer for storing the commands.
        -   `size_t len` - The length of the command buffer.
        -   `char *argv[]` - An array of command arguments.
    -   Return Value: None.
5. **print_error_message**:

    -   Description: Generates and prints an error message when a command is not found. It includes the command name and a "not found" message.
    -   Parameters:
        -   `char *argv[]` - An array of command arguments.
        -   `char *args[]` - An array of command arguments (specifically, the command that was not found).
        -   `char *error_message` - A buffer for storing the error message.
        -   `int length` - The length of the error message.
    -   Return Value: None.


V - File-based command execution (file_based_execution.c):
==========================================================
1. **execute_commands_from_file**:

    -   Description: Reads and executes commands from files. It opens each specified file, reads the commands, inserts them into the command history, and executes them.
    -   Parameters:
        -   `int argc` - The number of command-line arguments.
        -   `char *argv[]` - An array of command arguments (file names).
        -   `char *cmd` - A buffer for storing the commands.
        -   `size_t len` - The length of the command buffer.
    -   Return Value: None.
    
VI - Main function (main.c):
=============================
1. **main**:

    -   Description: The main function of the shell. It sets up signal handling, checks the history file, reads history, and then enters interactive or non-interactive mode based on command-line arguments. In the end, it writes history to the file, clears the history, and frees allocated memory.
    -   Parameters:
        -   `int argc` - The number of command-line arguments.
        -   `char *argv[]` - An array of command arguments.
    -   Return Value:
        -   `int` - The exit status of the program (0 for success, non-zero for failure).
    
VII - Environment variable operations (environment_variable_operations.c):
==========================================================================
1. **_getenv**:

    -   Description: Retrieves the value of an environment variable by searching through the `environ` array. It matches the variable name and returns the corresponding value.
    -   Parameters:
        -   `const char *name` - The name of the environment variable to retrieve.
    -   Return Value:
        -   `char *` - The value of the environment variable.



---------------------------------------------------------------------------------------------------------
Workflow
========

Here's the overall workflow of this shell program:

1\. The program starts by initializing the command history, registering signal handlers, and checking the history file.

2\. In interactive mode, the program displays the prompt and waits for user input.

3\. When a command is entered, it is read from the standard input, checked for length, inserted into the command history, and executed using `execute_cmd`.

4\. If the command is "cd", the `execute_cd_command` function is called to handle the change of directory.

5\. For any other command, the `execute_other_command` function is called to execute the command.

6\. During the execution, if a child process is created, it attempts to execute the command using `execve`. If the execution fails, it searches for the command in the directories specified in the "PATH" environment variable.

7\. If the command is not found or cannot be executed, an error message is displayed.

8\. After executing the command, the program writes the command history to the history file.

9\. In batch mode, the program reads commands from one or more files, inserts them into the command history, and executes them using `execute_cmd`.

10\. When the program receives a SIGINT or SIGTSTP signal, the appropriate signal handler functions are called, displaying the appropriate prompt message.

11\. The program provides functionality to store the command history by inserting each command into a linked list data structure.

12\. The `write_history` function is responsible for writing the command history to a file named "history.txt". It opens the file, iterates through the linked list, writes each command to the file, and closes the file.

13\. The `read_history` function reads the command history from the "history.txt" file. It opens the file, reads commands line by line, removes newline characters, and inserts each command into the command history.

14\. The `clear_history` function clears the entire command history by traversing the linked list and freeing each node.

15\. The `execute_commands_from_file` function allows the program to execute commands from one or more files. It opens each file, reads commands line by line, inserts them into the command history, and executes them using the `execute_cmd` function.

16\. The program also provides the functionality to change directories using the "cd" command. The `execute_cd_command` function handles the "cd" command, checking if an argument is provided and calling the `chdir` function to change the current working directory accordingly.

17\. The program includes utility functions like `_getenv`, `strcpy`, and `strcat` to retrieve environment variables, copy strings, and concatenate strings respectively.

18\. The program displays a shell prompt, and the user of the shell type in a command using the `print_prompt` function.

19\. The program handles both interactive and batch modes. In interactive mode, the program waits for user input, reads commands, inserts them into the command history, and executes them. In batch mode, the program reads commands from files, inserts them into the command history, and executes them.
