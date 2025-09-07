#include <string.h>
#include <stdio.h>
#include <readline/history.h>
#include "nsh/nsh.h"

char *handle_history_path(char *home_path)
{
    char *history_path = NULL;
    size_t path_size = 0;

    if (!home_path)
        return NULL;
    path_size = strlen(home_path) + strlen(HISTORY_FILE) + 1;
    history_path = xcalloc(path_size, sizeof(char));
    snprintf(history_path, path_size, "%s%s", home_path, HISTORY_FILE);
    return history_path;
}

nsh_t *init_shell_struct(char **env)
{
    nsh_t *shell = xcalloc(2, sizeof(nsh_t));
    shell->env = dup_env(env);
    shell->hard_input = NULL;
    shell->input = NULL;
    shell->last_status = 0;
    shell->local_env = NULL;
    shell->home = get_home();
    shell->history_path = handle_history_path(shell->home);
    return shell;
}

void destroy_shell_struct(nsh_t *shell)
{
    char **env_ptr = shell->env;

    while (shell->env && *env_ptr)
    {
        my_free(*env_ptr);
        env_ptr++;
    }
    my_free(shell->env);
    my_free(shell->home);
    my_free(shell->history_path);
    my_free(shell);
}

void leave_shell(nsh_t *shell)
{
    if (shell->history_path)
        write_history(shell->history_path);
    destroy_shell_struct(shell);
}