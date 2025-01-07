#include "shell.h"
/**
 * execute_cd_command - executes the "cd" command to change directories.
 * @args: array of command arguments
 * @env: array of character
 * Description: This function handles the "cd" command, which is used to change
 * directories. If no argument is provided, an error message is printed
 * to standard error. If an argument is provided, the chdir function is called
 * to change the current directory. If chdir fails, an error message is printed
 * to standard error.
 **/

void execute_cd_command(char *args[], char **env)
{
	const char *error_msg;

	if (args[1] == NULL)
	{
		error_msg = "cd: expected argument\n";
		if (write(STDERR_FILENO, error_msg, strlen(error_msg)) == -1)
		{
			perror("Write failed");
			exit(EXIT_FAILURE);
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		char *oldpwd = _getenv("OLDPWD", env);

		if (oldpwd == NULL)
		{
			error_msg = "cd: OLDPWD not set\n";
			if (write(STDERR_FILENO, error_msg, strlen(error_msg)) == -1)
			{
				perror("Write failed");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (chdir(oldpwd) != 0)
				perror("cd");
			else
				print_string(oldpwd);
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
}


/**
 * execute_command_in_path - Executes a command by
 * searching in the system's PATH.
 * @args: Array of command arguments.
 * @error_message: Error message buffer.
 * @length: Pointer to the length of the error message.
 * @env: The environment variables array
 * Description: This function searches for the command specified by
 * the first argument in the args array within the directories listed in the
 * system's PATH environment variable. If the command is found and
 * is executable it is executed using the execve function.
 * The error_message and length parameters are not used in this implementation.
 **/
void execute_command_in_path(char *args[], char *error_message,
		int *length, char **env)
{
	char *path = getenv("PATH");
	char *dir = strtok(path, ":");
	char exec_path[MAX_CMD_LEN];

	(void)error_message;
	(void)length;
	while (dir != NULL)
	{
		strcpy(exec_path, dir);
		strcat(exec_path, "/");
		strcat(exec_path, args[0]);
		if (access(exec_path, X_OK) == 0)
		{
			execve(exec_path, args, env);
			break;
		}
		dir = strtok(NULL, ":");
	}
}

/**
 * execute_other_command - Executes a command not handled by built-in commands.
 * @args: Array of command arguments.
 * @argv: Array of command-line arguments.
 * @env: The environment variables array
 * Description: This function forks a new process and attempts to execute the
 * command specified by the first argument in the args array.
 * If the execution fails, it tries to find the command in the system's PATH
 * If the command is still not found, an error message is printed
 * The parent process waits for the childm process
 * to complete before continuing.
 **/
void execute_other_command(char *args[], char *argv[], char **env)
{
	int length = 0;
	char error_message[1024];
	pid_t pid;

	if (!command_exists(args[0], env))
	{
		print_error_message(argv, args, error_message, length);
		return;
	}

	pid = fork();

	if (pid < 0)
	{
		handle_fork_error();
	}
	else if (pid == 0)
	{
		handle_child_process(args, argv, error_message, length, env);
	}
	else
	{
		handle_parent_process(pid);
	}
}

/**
 * execute_cmd - Executes a command
 * @cmd: The command to be executed
 * @argv: The arguments for the command
 * @data: A pointer to the shell data
 * @env: A pointer to the environment variables array
 */
void execute_cmd(char **cmd, char *argv[], shell_data *data, char **env)
{
	char *args[MAX_CMD_LEN] = {NULL};
	int i = 0;
	(void)data;

	while (cmd[i] != NULL)
	{
		args[i] = cmd[i];
		i++;
	}
	args[i] = NULL;

	if (args[0])
	{
		if (strncmp(args[0], "cd", 2) == 0)
		{
			execute_cd(args, env);
		}
		else if (strncmp(args[0], "env", 3) == 0)
		{
			execute_env(args, env);
		}
		else if (strncmp(args[0], "setenv", 6) == 0)
		{
			execute_setenv(args, env);
		}
		else if (strncmp(args[0], "unsetenv", 8) == 0)
		{
			execute_unsetenv(args, env);
		}
		else
		{
			execute_other_command(args, argv, env);
		}
	}
}

/**
 * free_commands - Frees the memory occupied by the command history list.
 * @data: Pointer to the shell_data struct.
 * Description: This function traverses the command history list and frees
 * the memory occupied by each node. After freeing the memory,
 * the head of the history list is set to NULL.
 **/
void free_commands(shell_data *data)
{
	Node *current = data->head;
	Node *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	data->head = NULL;
}
