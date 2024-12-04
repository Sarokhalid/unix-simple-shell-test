#include "shell.h"
/**
 * _getenv - Retrieves the value of an environment variable.
 * @name: The name of the environment variable.
 * @env: The environment variables array
 * Return: A pointer to the value of the environment variable
 * or NULL if not found.
 **/

char *_getenv(const char *name, char **env)
{
	size_t nameLength = strlen(name);
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(name, env[i], nameLength) == 0 &&
				env[i][nameLength] == '=')
		{
			return (env[i] + nameLength + 1);
		}
	}

	return (NULL);
}

/**
 * print_env - Prints the environment variables.
 * @env: Null-terminated array of strings representing the environment.
 *
 * Description: This function iterates over each string in the 'env' array,
 * which represents an environment variable, and writes it to stdout. Each
 * environment variable is printed on a new line.
 */
void print_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		/* Write the environment variable to stdout */
		write(STDOUT_FILENO, env[i], strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * set_env_var - Sets an environment variable
 * @name: The name of the environment variable
 * @value: The value to be set for the environment variable
 * @env: A pointer to the environment variables array
 *
 * Return: Nothing
 */
void set_env_var(char *name, char *value, char ***env)
{
	int i;
	char *new_env_var;

	/* Check if environment variable already exists */
	for (i = 0; (*env)[i] != NULL; i++)
	{
		if (strncmp(name, (*env)[i], strlen(name)) == 0
				&& (*env)[i][strlen(name)] == '=')
		{
			/* If it exists, modify the value */
			new_env_var = malloc(strlen(name) + strlen(value) + 2);
			if (new_env_var == NULL)
			{
				write(STDERR_FILENO, "Failed to allocate memory\n", 26);
				return;
			}
			strcpy(new_env_var, name);
			strcat(new_env_var, "=");
			strcat(new_env_var, value);
			free((*env)[i]);
			(*env)[i] = new_env_var;
			return;
		}
	}
	/* If it doesn't exist, create a new environment variable */
	new_env_var = malloc(strlen(name) + strlen(value) + 2);
	if (new_env_var == NULL)
	{
		write(STDERR_FILENO, "Failed to allocate memory\n", 26);
		return;
	}
	strcpy(new_env_var, name);
	strcat(new_env_var, "=");
	strcat(new_env_var, value);

	/* Add the new environment variable to the env array */
	(*env)[i] = new_env_var;
	(*env)[i + 1] = NULL;
}

/**
 * unset_env_var - Unsets an environment variable
 * @name: The name of the environment variable to be unset
 * @env: A pointer to the environment variables array
 *
 * Return: Nothing
 */
void unset_env_var(char *name, char ***env)
{
	int i;
	int found = 0; /* Add a flag to check if the variable was found */

	/* Find the environment variable */
	for (i = 0; (*env)[i] != NULL; i++)
	{
		if (strncmp(name, (*env)[i], strlen(name)) == 0
				&& (*env)[i][strlen(name)] == '=')
		{
			free((*env)[i]);

			/* Shift all elements down one spot */
			while ((*env)[i] != NULL)
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			(*env)[i] = NULL;

			found = 1; /* Set the flag to true */
			break;
		}
	}
	/* If the variable was not found, print an error message */
	if (!found)
	{
		char *error_message = malloc(strlen(name) + 42);

		if (error_message == NULL)
		{
			write(STDERR_FILENO, "Failed to allocate memory\n", 26);
			return;
		}
		strcpy(error_message, "Error: Environment variable '");
		strcat(error_message, name);
		strcat(error_message, "' not found\n");
		write(STDERR_FILENO, error_message, strlen(error_message));
		free(error_message);
	}
}
