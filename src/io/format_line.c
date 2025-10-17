#include "nsh/nsh.h"
#include <readline/history.h>

int history_expansion(nsh_t *shell)
{
    char *base = shell->hard_input;
    char *exp = NULL;

    history_expand(base, &exp);
    if (!exp) {
        shell->input = xstrdup(shell->hard_input);
        return -1;
    }
    shell->input = exp;
    add_history(shell->input);
    return 0;
}

int format_line(nsh_t *shell)
{
    history_expansion(shell);
    return 0;
}