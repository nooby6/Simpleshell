#include "shell.h"

int main(void) {
    char *input;

    while (1) {
        display_prompt();
        input = read_input();
        if (input == NULL) {
            printf("\n");
            break;
        }
        execute_command(input);
        free(input);
    }

    return (0);
}
