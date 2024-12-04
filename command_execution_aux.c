#include "shell.h"

/**
 * execute_cd - Executes the 'cd' command
 * @args: The arguments for the 'cd' command
 * @env: A pointer to the environment variables array
 */
void execute_cd(char **args, char **env)
{
	execute_cd_command(args, env);
}

/**
 * execute_env - Executes the 'env' command
 * @args: The arguments for the 'env' command
 * @env: A pointer to the environment variables array
 */
void execute_env(char **args, char **env)
{
	(void)args;
	print_env(env);
}

/**
 * execute_setenv - Executes the 'setenv' command
 * @args: The arguments for the 'setenv' command
 * @env: A pointer to the environment variables array
 */
void execute_setenv(char **args, char **env)
{
	if (args[1] && args[2]) /* Check if VARIABLE and VALUE are provided */
	{
		set_env_var(args[1], args[2], &env);
	}
	else
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
	}
}

/**
 * execute_unsetenv - Executes the 'unsetenv' command
 * @args: The arguments for the 'unsetenv' command
 * @env: A pointer to the environment variables array
 */
void execute_unsetenv(char **args, char **env)
{
	if (args[1]) /* Check if VARIABLE is provided */
	{
		unset_env_var(args[1], &env);
	}
	else
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
	}
}

