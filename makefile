$(CC) = gcc
shell:
	$(CC)	command_execution.c	command_history.c	file_based_execution.c	handle_semicolon.c	main.c	shell.h	_term.c	command_execution_aux.c	environment_variable_operations.c	handle_comments.c	interactive_shell_operations.c	signal_handling.c  -o shell
Clean:
	rm *.o shell
