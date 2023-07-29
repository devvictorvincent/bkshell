#ifndef _SHELL_H
#define _SHELL_H

extern char **environ;

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


int _execute(char *cmd, char *cmd_arr[], char *arg);
char **tokenizeString(char *inputString);
int my_env(char *cmd);
char *findShellCommandPath(const char *command);

#endif

