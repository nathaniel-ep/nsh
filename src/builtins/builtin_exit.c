#include "nsh/nsh.h"

int builtin_exit(MU int ac, MU char **av, nsh_t *shell)
{
    //free_arr(av);
    leave_shell(shell);
    exit(0);
}