#include "nsh/nsh.h"

int format_line(nsh_t *shell)
{
    shell->input = xstrdup(shell->hard_input);
    return 0;
}