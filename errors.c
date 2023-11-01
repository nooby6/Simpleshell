#include "shell.h"

void handle_error(char *message) {
    perror(message);
}
