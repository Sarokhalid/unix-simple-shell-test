#include "shell.h"
/**
 * handle_sigint - Handles the SIGINT signal (Ctrl+C) in the shell.
 * @signum: The signal number.
 * Description: This function is a signal handler for the
 * SIGINT signal (Ctrl+C).
 * It is used in a shell to handle the interruption of a running command.
 * The function simply writes a newline and a prompt "$ "
 * to the standard output, effectively displaying a new prompt line
 * after the interruption.
 * The (void)signum is used to explicitly indicate that the signum parameter
 * is unused to avoid a warning about an unused variable.
 **/

void handle_sigint(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n$ ", 4);
	fflush(stdout);
}

/**
 * handle_sigtstp - Handles the SIGTSTP signal (Ctrl+Z) in the shell.
 * @signum: The signal number.
 * Description: This function is a signal handler for the
 * SIGTSTP signal (Ctrl+Z).
 * It is used in a shell to handle the suspension of a running command.
 * The function simply writes a newline character to the standard output
 * effectively displaying a new line after suspending a command.
 * The (void)signum is used to explicitly indicate that the
 * signum parameter is unused to avoid a warning about an unused variable.
 **/

void handle_sigtstp(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 2);
}

/**
 * handle_signals - Sets up signal handlers
 * for SIGINT and SIGTSTP in the shell.
 * Description: This function sets up signal handlers for the SIGINT (Ctrl+C)
 * and SIGTSTP (Ctrl+Z) signals in a shell.It assigns the corresponding
 *  signal handlers.
 * handle_sigint and handle_sigtstp, to the respective signals.
 * This allows the shell to handle interruptions (Ctrl+C)
 * and suspensions (Ctrl+Z) gracefully.
 **/
void handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGTSTP, handle_sigtstp);
}
