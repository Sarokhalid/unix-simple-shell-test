#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>

#define MAX_CMD_LEN 10240
#define HISTORY_COUNT 10
#define HISTORY_FILE "history.txt"


/**
 * struct Node - Linked list node structure.
 * @cmd: Array to store the command string.
 * @next: Pointer to the next node in the linked list.
 * Description: This structure represents a node in a linked list. It contains
 * a fixed-size array `cmd` to store the command string and a
 * pointer `next` to the next node in the linked list.
 **/
typedef struct Node
{
	char cmd[MAX_CMD_LEN];
	struct Node *next;
} Node;

/**
 * struct shell_data - Shell data structure.
 * @head: Pointer to the head node of the linked list.
 * Description: This structure represents the shell data. It contains a pointer
 * `head` to the head node of a linked list. The linked list
 * stores commands, where each node represents a command in the list
 **/
typedef struct shell_data
{
	Node *head;
} shell_data;

char *_trim(char *str);
int _isspace(char c);
int is_whitespace(char c);

/* Signal handling functions */
void handle_signals(void);
void handle_sigint(int signum);
void handle_sigtstp(int signum);

/* Environment variable functions */
char *_getenv(const char *name, char **env);
void print_env(char **env);
void set_env_var(char *name, char *value, char ***env);
void unset_env_var(char *name, char ***env);

/* Command execution functions */
void execute_cmd(char **cmd, char *argv[], shell_data *data, char **env);
void execute_cd_command(char *args[], char **env);
void execute_other_command(char *args[], char *argv[], char **env);
void execute_command_in_path(char *args[], char *error_message,
		int *length, char **env);
void execute_cd(char **args, char **env);
void execute_env(char **args, char **env);
void execute_setenv(char **args, char **env);
void execute_unsetenv(char **args, char **env);

/* Command existence check function */
int command_exists(char *cmd, char **env);

/* Process handling functions */
void handle_fork_error(void);
void handle_child_process(char *args[], char *argv[],
		char *error_message, int length, char **env);
void handle_parent_process(pid_t pid);

/* Error message printing function */
void print_error_message(char *argv[], char *args[],
		char *error_message, int length);

/* Command reading functions */
void read_command(char **cmd, size_t *len);
void read_and_execute_commands(FILE *fd, char *argv[],
		shell_data data, char **env);

/* Command parsing functions */
void check_command_length(char *cmd);
void handle_comments(char *cmd);
void handle_semicolon(char *cmd, char *argv[],
		shell_data *data, char **env);
void split_and_execute_cmd(char *trim_cmd, char *argv[],
		shell_data *data, char **env);
void reset_args(char *args[], int *arg_count);

/* Command history functions */
void check_history_file(void);
void insert_cmd(shell_data *data, const char *cmd);
void clear_history(shell_data *data);
void write_history(shell_data *data);
void read_history(shell_data *data);

/* Command mode functions */
void execute_commands_from_file(int argc, char *argv[],
		shell_data data, char **env);
void execute_commands_interactively(char *cmd, size_t len,
		char *argv[], shell_data *data, char **env);

/* Prompt printing function */
void print_prompt(void);

/* Command freeing function */
void free_commands(shell_data *data);
void print_string(const char *string);

#endif /** shell.h **/
