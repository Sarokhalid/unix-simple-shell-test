#include "shell.h"
/**
 * handle_comments - Handles comments in the given command string.
 * @cmd: The command string to process.
 * This function modifies the command string by removing any comments
 * starting with a '#' symbol. If the '#' symbol is part of a word and
 * not a comment, it is preserved.
 **/
void handle_comments(char *cmd)
{
	char *cs = cmd;

	while (*cs != '\0')
	{
		if (*cs == '#')
		{
			if (cs != cmd && !is_whitespace(*(cs - 1)))
			{
				cs++;
				continue;
			}
			else
			{
				*cs = '\0';
				break;
			}
		}
		cs++;
	}
}

/**
 * is_whitespace - Checks if the given character is a whitespace character.
 * @c: The character to check.
 * Return: 1 if the character is a whitespace character, 0 otherwise.
 **/

int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
