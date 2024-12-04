#include "shell.h"
/**
 * _trim - Trims leading and trailing whitespace characters from a string
 * @str: The string to be trimmed.
 * Return: A pointer to the trimmed string, or NULL if str is NULL
 **/
char *_trim(char *str)
{
	char *st = str;
	char *en = str + strlen(str) - 1;

	if (str == NULL)
		return (NULL);
	while (_isspace(*st))
		st++;
	while (en > st && _isspace(*en))
		en--;
	*(en + 1) = '\0';
	return (st);
}

/**
 * _isspace - Checks if a character is a whitespace character.
 * @c: The character to be checked.
 * Return: 1 if the character is a whitespace character, 0 otherwise.
 **/
int _isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}

/**
 * command_exists - Checks if a command exists in the PATH
 * or is a full path to an executable.
 * @cmd: The command to check.
 * @env: The environment variables array
 *
 * Return: 1 if the command exists, 0 otherwise.
 */
int command_exists(char *cmd, char **env)
{
	char *path;
	char *path_copy;
	char *dir;
	char exec_path[MAX_CMD_LEN];

	/* Check if cmd is a full path to an executable */
	if (access(cmd, X_OK) == 0)
	{
		return (1);
	}

	/* If not, check if cmd exists in the PATH */
	path = _getenv("PATH", env);
	path_copy = strdup(path);  /* Make a copy of PATH */
	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		strcpy(exec_path, dir);
		strcat(exec_path, "/");
		strcat(exec_path, cmd);
		if (access(exec_path, X_OK) == 0)
		{
			free(path_copy);  /* free the copy */
			return (1);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);  /* free the copy */
	return (0);
}

/**
 * reset_args - Resets the arguments array and argument
 * count for the next command.
 * @args: The arguments array to reset.
 * @arg_count: The argument count to reset.
 *
 * Return: void
 */
void reset_args(char *args[], int *arg_count)
{
	int j;

	*arg_count = 0; /* Reset argument count for next command */

	/* Reset arguments array for next command */
	for (j = 0; j < MAX_CMD_LEN; j++)
	{
		args[j] = NULL;
        }
}

/**
 ** print_string - Prints a null-terminated string to the standard output
 ** @string: The string to be printed
 ** Description:
 ** This function prints each character of the given string until it reaches
 ** the null terminator '\0'. It assumes that a valid null-terminated string
 ** is passed as an argument.
 ***/
void print_string(const char *string)
{
	        int k;

		        for (k = 0; string[k] != '\0'; k++)
				        {
						                putchar(string[k]);
								        }
}
