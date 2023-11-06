#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function to read a line of input using dynamic memory allocation */
char *custom_getline(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;

    ssize_t characters = getline(&buffer, &bufsize, stdin);

    if (characters == -1)
    {
        perror("Error reading input");
        free(buffer);
        exit(1);
    }

    buffer[characters - 1] = '\0'; /* Remove the trailing newline character */

    return buffer;
}

int main(int argc, char *argv[])
{
    if (argc > 1) /* Non-interactive mode */
    {
        FILE *input_file = fopen(argv[1], "r");
        if (input_file == NULL)
        {
            perror("File open error");
            exit(1);
        }

        char *input = NULL;
        size_t bufsize = 0;
        ssize_t characters;

        while ((characters = getline(&input, &bufsize, input_file)) != -1)
        {
            input[characters - 1] = '\0'; /* Remove the trailing newline character */

            /* Handle non-interactive shell logic */

            pid_t child_pid = fork();

            if (child_pid == -1)
            {
                perror("Fork error");
                free(input);
                exit(1);
            }

            if (child_pid == 0)
            {
                char *args[10];
                args[0] = input;
                args[1] = NULL;

                if (execvp(args[0], args) == -1)
                {
                    perror("Execution Error");
                    free(input);
                    exit(1);
                }
            }
            else
            {
                int status;
                waitpid(child_pid, &status, 0);
            }
        }

        free(input);
        fclose(input_file);
    }
    else /* Interactive mode */
    {
        char *input;
	char *args[10];

        while (1)
        {
            printf("($) "); /* Display the shell prompt */
            input = custom_getline(); /* Read a line of input */

            if (input[0] == '\0') /* Check for empty input and ignore it */
                continue;

            /* Handle interactive shell logic */

            if (strcmp(input, "exit") == 0)
	    {
                free(input);
		exit(0);
            }
            else if (strcmp(input, "env") == 0)
            {
                extern char **environ;
                char **env = environ;
                while (*env)
                {
                    printf("%s\n", *env);
                    env++;
                }
            }
            else
            {
                pid_t child_pid = fork();

                if (child_pid == -1)
                {
                    perror("Fork error");
                    free(input);
                    exit(1);
                }

                if (child_pid == 0)
                {
                    args[0] = input;
                    args[1] = NULL;

                    if (execvp(args[0], args) == -1)
                    {
                        perror("Execution Error");
                        free(input);
                        exit(1);
                    }
                }
                else
                {
                    int status;
                    waitpid(child_pid, &status, 0);
                }
            }

            free(input);
        }
    }

    return 0;
}

