#include "shell.h"

/* Function to handle the "exit" built-in command */
void handle_exit() {
    exit(0);
}

/* Function to handle the "ls" built-in command */
void handle_ls() {
    system("ls");
}

/* Function to handle the "cat" built-in command */
void handle_cat(char *file) {
    char command[256];
    snprintf(command, sizeof(command), "cat %s", file);
    system(command);
}

/* Function to handle the "mv" built-in command */
void handle_mv(char *source, char *destination) {
    char command[256];
    snprintf(command, sizeof(command), "mv %s %s", source, destination);
    system(command);
}

/* Function to handle the "touch" built-in command */
void handle_touch(char *file) {
    char command[256];
    snprintf(command, sizeof(command), "touch %s", file);
    system(command);
}
