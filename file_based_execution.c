#include "shell.h"

/**
 * execute_commands_from_file - reads and executes commands
 * from one or more input files specified in the command
 * line arguments.
 *
 * @argc:   The number of command line arguments.
 * @argv:   An array of strings containing the command line arguments.
 * @data:   A data structure to manage shell-related information.
 * @env: The environment variables array
 */
void execute_commands_from_file(int argc, char *argv[],
		shell_data data, char **env)
{
	int i;
	FILE *fd;

	data.head = NULL;
	for (i = 1; i < argc; i++)
	{
		/* Open the command file */
		fd = fopen(argv[i], "r");
		if (fd == NULL)
		{
			perror("Failed to open command file");
			exit(EXIT_FAILURE);
		}

		read_and_execute_commands(fd, argv, data, env);
		/* Close the command file */
		if (fclose(fd) != 0)
		{
			perror("Failed to close command file");
		}
		clear_history(&data);
		free_commands(&data);
	}
}

/**
 * read_and_execute_commands - Reads commands from
 * a file and executes them.
 * @fd: The file descriptor of the command file.
 * @argv: The arguments that were passed to the program.
 * @data: The shell data structure.
 * @env: The environment variables array
 *
 * Return: void
 */
void read_and_execute_commands(FILE * fd, char *argv[],
		shell_data data, char **env)
{
	
	char cmd[MAX_CMD_LEN];

	/* Read commands from the file */
	while (fgets(cmd, MAX_CMD_LEN, fd) != NULL)
	{
		size_t len = strlen(cmd);
		if (len > 0 && cmd[len - 1] == '\n')
		{
		    cmd[len -1] = '\0';
		}
		handle_comments(cmd);
		if (strlen(cmd) == 0)
		{
		    continue;
		}
		if (strncmp(cmd, "exit", 4) == 0 || strncmp(cmd, "quit", 4) == 0)
		{
		    break;
		}
		handle_semicolon(cmd, argv, &data, env);
	}
}

/**
 * handle_fork_error - Handles a fork error by printing an
 * error message and exiting the program.
 *
 * Return: Does not return as the program is exited.
 */
void handle_fork_error(void)
{
	perror("Fork failed");
	exit(EXIT_FAILURE);
}

/**
 * handle_child_process - Handles the child process after a
 * fork by executing the command.
 * @args: The arguments for the command to execute.
 * @argv: The arguments that were passed to the program.
 * @error_message: The error message to print if the
 * command cannot be executed.
 * @length: The length of the error message.
 * @env: The environment variables array
 *
 * Return: void
 */
void handle_child_process(char *args[], char *argv[],
		char *error_message, int length, char **env)
{
	/* Try to execute the command directly */
	if (execvp(args[0], args) == -1)
	{
		execute_command_in_path(args, error_message, &length, env);
		/* If we still can't execute the command, print an error message */
		print_error_message(argv, args, error_message, length);
		exit(127);
	}
}

/**
 * handle_parent_process - Handles the parent process after a
 * fork by waiting for the child process to finish.
 * @pid: The process ID of the child process.
 *
 * Return: void
 */
void handle_parent_process(pid_t pid)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status)) /* If the child process exited normally*/
	{
		int child_exit_status = WEXITSTATUS(status);

		if (child_exit_status == 127)
		{
			exit(127); /* Exit the parent process with status 127 */
		}
	}
}
