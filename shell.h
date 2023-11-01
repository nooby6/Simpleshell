#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>

/* Function Prototypes */
void display_prompt(void);
char *read_input(void);
char **parse_command(char *command);
void execute_command(char *command);
void handle_error(char *message);
int execute_exit(void);
void execute_env(void);

#endif
