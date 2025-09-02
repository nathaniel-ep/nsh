#include "nsh/nsh.h"
#include <stdio.h>
#include <string.h>

char **dup_env(char **env)
{
    char **new_env = NULL;
    int nmemb = 0;
    void *ptr = env;

    if (!env || !(env[0]))
        return NULL;
    while (*env) {
        nmemb++;
        env++;
    }
    env = ptr;
    new_env = xcalloc(nmemb + 1, sizeof(char *));
    ptr = new_env;

    while (*env) {
        *new_env = xstrdup(*env);
        env++;
        new_env++;
    }
    
    return ptr;
}