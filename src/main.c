#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "nsh/nsh.h"

int main(MU int ac, MU char **av, char **env)
{
    nsh_t *shell = init_shell_struct(env);

    shell->hard_input = readline("$> ");
    while (shell->hard_input)
    {
        printf("you wrote: %s\n", shell->hard_input);
        my_free(shell->hard_input, strlen(shell->hard_input));
        shell->hard_input = readline("$> ");
    }
    destroy_shell_struct(shell);
    return 0;
}
