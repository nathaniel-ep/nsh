#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <readline/history.h>
#include "nsh/nsh.h"

int init_history(char *path)
{
    using_history();
    if (!path)
        return 84;
    read_history(path);
    return 0;
}