#include "shell.h"

/**
 * findShellCommandPath - finds path to command
 * @command: command arguments given
 *  * Return: Always 0.
 */
char *findShellCommandPath(const char *command)
{
	char *fullCommandPath = NULL, *path, *token;
	char *pathEnv = getenv("PATH");
	char *commandPath;

	if (pathEnv == NULL)
	{
		perror("Error");
		return (NULL);
	}
	path = strdup(pathEnv);
	token = strtok(path, ":");
	while (token != NULL)
	{
		commandPath = (char *)malloc(strlen(token) + strlen(command) + 2);

		if (commandPath == NULL)
		{
			perror("Error");
			free(path);
			return (NULL);
		}
		sprintf(commandPath, "%s/%s", token, command);
		if (access(commandPath, X_OK) == 0)
		{
			fullCommandPath = commandPath;
			break;
		}
		free(commandPath);
		token = strtok(NULL, ":");
	}
	free(path);
	return (fullCommandPath);
}
