#include "nsh/nsh.h"
#include <readline/history.h>

int history_format(nsh_t *shell)
{
    // to do stop at 14 oct 2025 first task to do
}

int format_line(nsh_t *shell)
{
    shell->input = xstrdup(shell->hard_input);
    return 0;
}