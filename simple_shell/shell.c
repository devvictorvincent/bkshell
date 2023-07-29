#include "shell.h"


/**
 * main - main entery point function
 * @argc: no of command line arguments
 * @argv: array of command line functions
 *  * Return: Always 0.
 */

int main(int argc, char **argv)
{
	size_t n = 10;
	int piped_input = !isatty(STDIN_FILENO);
	char *str = NULL, **cmd_arr, *fpath;

	while (1)
	{
		if (argc > 1)
		{
			fpath = findShellCommandPath(argv[1]);
			_execute(argv[1], argv, argv[0]);
			wait(NULL);
			break;
		}
		else
		{
			write(2, "#cisfun$ ", strlen("#cisfun$ "));
			if (getline(&str, &n, stdin) == -1)
			{
				free(str);
				break;
			}
			cmd_arr = tokenizeString(str);
			my_env(cmd_arr[0]);
			if (strcmp(cmd_arr[0], "exit") == 0)
			{
				free(cmd_arr);
				free(str);
				break;
			}
			fpath = findShellCommandPath(cmd_arr[0]);
			if (fpath == NULL)
				fpath = cmd_arr[0];
			_execute(fpath, cmd_arr, argv[0]);
			wait(NULL);
			free(cmd_arr);
			free(fpath);
		}
		if (piped_input)
			break;
	}
	return (0);
}
/**
 *_execute - executes commands and executes them
 * @cmd: cmd for command passed
 * @cmd_arr: cmd_arr for command array
 * @arg: arg for filename cmd arg first
 *  * Return: returns 0 if it succeds of -1 if fails.
 */
int _execute(char *cmd, char *cmd_arr[], char *arg)
{
	int val;
	int wpid;
	char *my_environ[] = {"CUSTOM_VAR=custom_value", NULL};

	wpid = fork();
	if (wpid == 0)
	{
		val = execve(cmd, cmd_arr, my_environ);
	}
	if (val == -1)
	{
		perror(arg);
	}
return (0);
}


/**
 * tokenizeString - tokenises strings given
 * @inputString: inputString passed to be tokenized
 *  * Return: Always string.
 */
char **tokenizeString(char *inputString)
{
	char **str = malloc(sizeof(char *) * strlen(inputString));
	char *delim = " \n";
	int i = 1;
	char *token;

	token = strtok(inputString, delim);
	str[0] = token;
	while (token != NULL)
	{
		token = strtok(NULL, delim);
		str[i] = token;
		i++;
	}
	return (str);
}
/**
 * my_env - my_env executes env commands
 * @cmd: passed command
 *  * Return: Always 0.
 */
int my_env(char *cmd)
{
	char **env;

	if (strcmp(cmd, "env") == 0)
	{
		env = environ;

		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	}
	return (0);
}
