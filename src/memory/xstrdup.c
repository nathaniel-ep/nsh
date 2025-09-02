#include <string.h>
#include <stdlib.h>
char *xstrdup(char *src)
{
    char *str = NULL;
    if (!src)
        return NULL;
    str = strdup(src);
    if (!str) {
        perror("malloc");
        exit(84);
    }
    return str;
}