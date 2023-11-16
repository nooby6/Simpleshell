#include "my_shell.h"

int main(int argc, char *argv[])
{
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
