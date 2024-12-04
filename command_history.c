#include "shell.h"
/**
 * insert_cmd - Inserts a command into the history list.
 * @data: Pointer to the shell_data struct.
 * @cmd: Command string to be inserteted
 * Description: This function creates a new node, copies the command string
 * into the node, and inserts the node at the beginning of the history list
 * If the history list exceeds the maximum count the oldest commands are
 * removed from the list.If memory allocation fails, an error message is
 * printed,and the program terminates.
 **/

void insert_cmd(shell_data *data, const char *cmd)
{
	Node *newNode = (Node *)malloc(sizeof(Node));

	if (newNode == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	strcpy(newNode->cmd, cmd);
	newNode->next = data->head;
	data->head = newNode;

	if (HISTORY_COUNT > 0)
	{
		Node *current = data->head;
		Node *prev = NULL;

		int count = 0;

		while (current != NULL)
		{
			prev = current;
			current = current->next;
			count++;

			if (count >= HISTORY_COUNT)
			{
				prev->next = NULL;
				while (current != NULL)
				{
					prev = current;
					current = current->next;
					free(prev);
				}
				break;
			}
		}
	}
}
/**
 * clear_history - Frees the memory used by the history list.
 * @data: Pointer to the shell_data struct.
 * Description: This function frees the memory allocated for each node
 * in the history list of the shell_data struct.
 **/
void clear_history(shell_data *data)
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

/**
 * write_history - Writes the command history to a file.
 * @data: Pointer to the shell_data struct.
 * Description: This function opens a file,writes each command
 * in the history list to the file, and closes the file.
 * If any error occurs during the process, an error message
 * is printed and the function returns.
 **/
void write_history(shell_data *data)
{
	Node *current;
	ssize_t len;
	int fd;

	/* Open the file */
	fd = open(HISTORY_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("Failed to open history file for writing");
		return;
	}

	current = data->head;
	while (current != NULL)
	{
		/* Write the command to the file */
		len = strlen(current->cmd);
		if (write(fd, current->cmd, len) != len)
		{
			perror("Failed to write command to history file");
			close(fd);
			return;
		}

		/* Write a newline character */
		if (write(fd, "\n", 1) != 1)
		{
			perror("Failed to write newline to history file");
			close(fd);
			return;
		}

		current = current->next;
	}

	/* Close the file */
	if (close(fd) == -1)
	{
		perror("Failed to close history file");
	}
}
/**
 * read_history - Reads command history from a file and
 * inserts it into the shell_data struct.
 * @data: Pointer to the shell_data struct
 * Description: This function opens a history file,reads commands from it
 * removes newline characters, and inserts the commands into the history list
 * of the shell_data struct. If any error occurs during the process
 * an error message is printed and the function returns.
 **/
void read_history(shell_data *data)
{
	char cmd[MAX_CMD_LEN];
	ssize_t nread;
	int fd;

	/* Open the file */
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open history file for reading");
		return;
	}

	/* Read the commands from the file */
	while ((nread = read(fd, cmd, MAX_CMD_LEN)) > 0)
	{
		/* Remove the newline character, if present */
		if (cmd[nread - 1] == '\n')
		{
			cmd[nread - 1] = '\0';
		}
		insert_cmd(data, cmd);
	}

	/* Close the file */
	if (close(fd) == -1)
	{
		perror("Failed to close history file");
	}
}

/**
 * check_history_file - Checks if the history file exists
 * and creates it if necessary.
 * Description: This function checks if the history file exists
 * If the file doesn't exist, it creates the file with read and write
 * permissions for the user. If any error occurs during the process
 * an error message is printed, and the program terminates.
 **/
void check_history_file(void)
{
	int fd;
	/* Open the file */
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
	{
		/* The file doesn't exist; create it */
		fd = open(HISTORY_FILE, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		if (fd == -1)
		{
			perror("Failed to create history file");
			exit(EXIT_FAILURE);
		}
	}

	/* Close the file */
	if (close(fd) == -1)
	{
		perror("Failed to close history file");
	}
}
