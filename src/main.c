#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "nsh/nsh.h"
#include "lib/my_string.h"

int handle_line_and_history(nsh_t *shell)
{
    format_line(shell);
    if (*(shell->input))
        add_history(shell->input);
    printf("wrote %s\n", shell->input);
    return 0;
}

int main(MU int ac, MU char **av, char **env)
{
    nsh_t *shell = init_shell(env);

    shell->hard_input = readline("$> ");
    while (shell->hard_input) {
        handle_line_and_history(shell);
        builtin_exit(1, (char *[]){"exit", NULL}, shell);
        free_line(shell);
        shell->hard_input = readline("$> ");
    }
    leave_shell(shell);
    return 0;
}
