#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Entry point
 * *custom_getline - Function to read a line of input 
 * Return 0: Success
 *
 */
char *custom_getline(void)
{
    static char buffer[1024]; /* Static buffer to read input */
    memset(buffer, 0, sizeof(buffer)); /* Clear the buffer */

    char c;
    int index = 0;

    /* Read characters until a newline or the end of the file */
    while (1)
    {
        c = getchar();

        if (c == EOF || c == '\n')
        {
            buffer[index] = '\0'; /* Null-terminate the input */
            return buffer; /* Return the input line */
        }

        buffer[index] = c; /* Store the character in the buffer */
        index++;
    }
}

int main(void)
{
    char *input;
    while (1)
    {
        printf("$ "); /* Display the shell prompt */
        input = custom_getline(); /* Read a line of input */

        if (input[0] == '\0') /* Check for empty input and ignore it */
            continue;

        if (strcmp(input, "exit") == 0)
        {
            /* Implement the "exit" built-in */
            free(input); /* Free the memory used for input */
            exit(0); /* Exit the shell */
        }
        else if (strcmp(input, "env") == 0)
        {
            /* Implement the "env" built-in */
            extern char **environ; /* Access the environment variables */
            for (char **env = environ; *env; ++env)
            {
                printf("%s\n", *env); /* Print each environment variable */
            }
        }
        else
        {
            /* Handle non-built-in commands */
            pid_t child_pid = fork(); /* Fork a child process */

            if (child_pid == -1) /* Check for fork errors */
            {
                perror("Fork error"); /* Print an error message */
                free(input); /* Free the memory used for input */
                exit(1); /* Exit the shell with an error status */
            }

            if (child_pid == 0) /* In the child process */
            {
                /* Execute the command with arguments */
                char *args[10]; /* Array to store command and arguments */
                args[0] = input; /* Set the command as the first argument */
                args[1] = NULL; /* Null-terminate the argument list */

                if (execvp(args[0], args) == -1)
                {
                    perror("Execution Error"); /* Print an error message if execution fails */
                    free(input); /* Free the memory used for input */
                    exit(1); /* Exit the child process with an error status */
                }
            }
            else /* In the parent process */
            {
                int status;
                waitpid(child_pid, &status, 0); /* Wait for the child process to finish */
            }
        }

        free(input); /* Free the memory used for input */
    }

    return 0; /* Exit the shell with a success status */
}
