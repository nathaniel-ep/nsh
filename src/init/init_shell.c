#include "nsh/nsh.h"

nsh_t *init_shell(char **env)
{
    nsh_t *shell = init_shell_struct(env);
    init_history(shell->history_path);
    return shell;
}