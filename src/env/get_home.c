#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include "nsh/nsh.h"

char *get_home(void)
{
    char *home = getenv("HOME");
    char *path = NULL;
    size_t path_size = 0;
    MU uid_t uid = 0;
    MU struct passwd *pw = NULL;

    if (home) {
        path_size = strlen(home) + 2;
        path = xcalloc(path_size, sizeof(char));
        snprintf(path, path_size * sizeof(char), "%s/", home);
        return path;
    }
    uid = getuid();
    if (uid == 0) {
        path = xstrdup("/root/");
        return path;
    }
    pw = getpwuid(uid);
    if (!pw) {
        perror("getpwuid");
        return NULL;
    }
    path_size = strlen("/home/") + strlen(pw->pw_name) + 2;
    path = xcalloc(path_size, sizeof(char));
    snprintf(path, path_size, "/home/%s/", pw->pw_name);
    return path;
}