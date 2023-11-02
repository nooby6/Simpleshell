#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    while (1)
    {
        printf("$ "); /* Display the prompt */
        characters = getline(&input, &bufsize, stdin);

        if (characters == EOF) /* Check for end of file (Ctrl+D) */
        {
            printf("\n");
            free(input);
            exit(0);
        }

	 char *token = strtok(input, " ");
        char *args[10]; /* You can adjust the size as needed for your use case */

        int argCount = 0;
        while (token != NULL)
        {
            args[argCount] = token;
            argCount++;
            token = strtok(NULL, " ");
        }

        args[argCount] = NULL; /* Null-terminate the argument list */


        input[characters - 1] = '\0'; /* Remove the trailing newline character */

        pid_t child_pid = fork();

        if (child_pid == -1)
        {
            perror("Fork error");
            free(input);
            exit(1);
        }

        if (child_pid == 0)
        {
            /* Child process */
            char *args[2];
            args[0] = input;
            args[1] = NULL;

            if (execve(args[0], args, NULL) == -1)
            {
                perror("Error");
                free(input);
                exit(1);
            }
        }
        else
        {
            /* Parent process */
            int status;
            waitpid(child_pid, &status, 0); /* Wait for the child process to finish */
        }
    }

    free(input);
    return (0);
}

