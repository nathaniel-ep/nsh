#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "nsh/nsh.h"

int handle_line_and_history(nsh_t *shell)
{
    format_line(shell);
    if (*(shell->input))
        add_history(shell->input);
    for (int i = 0; BUILTIN_TAB[i].name; i++) {
        if (builtin_match(BUILTIN_TAB[i].tag, BUILTIN_TAB[i].name, shell->input)) {
            printf("builtin: %s detected\n", BUILTIN_TAB[i].name);
            return 0;
        }
    }
    printf("wrote %s\n", shell->input);
    return 0;
}

void free_line(nsh_t *shell)
{
    my_free(shell->hard_input);
    my_free(shell->input);
}

int main(MU int ac, MU char **av, char **env)
{
    nsh_t *shell = init_shell(env);

    shell->hard_input = readline("$> ");
    while (shell->hard_input)  {
        handle_line_and_history(shell);
        free_line(shell);
        shell->hard_input = readline("$> ");
    }
    leave_shell(shell);
    return 0;
}
