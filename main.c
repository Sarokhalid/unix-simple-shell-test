#include "shell.h"
/**
 * main - Entry point of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 * @env: The environment variables array
 * Return: 0 on successful execution
 **/

int main(int argc, char *argv[], char **env)
{
	char *cmd = NULL;
	size_t len = 0;
	shell_data data;

	data.head = NULL;

	handle_signals();

	if (argc > 1)  
	{
		/* Non-interactive mode: Read commands from files or pipes */
		struct stat st;

		if (stat(argv[1], &st) == 0 && S_ISREG(st.st_mode))
	        {
			/* If argv[1] is a file, read commands from the file */
			execute_commands_from_file(argc, argv, data, env);
                }	
		else
		{
			/* If argv[1] is not a file, treat it as a command */
			execute_cmd(argv + 1, argv, &data, env);
		}
        }   
	else
	{
		/* Interactive mode: Read commands from the user */
		execute_commands_interactively(cmd, len, argv, &data, env);
	}

	free_commands(&data);
	clear_history(&data);
	return (0);
}
