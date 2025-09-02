#include "nsh/nsh.h"
#include <string.h>
#include <stdio.h>

nsh_t *init_shell_struct(char **env)
{
    nsh_t *shell = xcalloc(2, sizeof(nsh_t));
    shell->env = dup_env(env);
    shell->hard_input = NULL;
    shell->input = NULL;
    shell->last_status = 0;
    shell->local_env = NULL;
    return shell;
}

void destroy_shell_struct(nsh_t *shell)
{
    char **env_ptr = shell->env;

    if (shell->hard_input)
        my_free(shell->hard_input, sizeof(char) * strlen(shell->hard_input) + 1);
    while (*env_ptr) {
        my_free(*env_ptr, strlen(*env_ptr) + 1);
        env_ptr++;
    }
    my_free(shell->env, 0);
    my_free(shell, sizeof(nsh_t));
}