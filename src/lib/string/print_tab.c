#include <stdio.h>

int print_arr(char **arr)
{
    char **ptr = arr;

    if (!ptr || !(*ptr))
        return -1;
    while (*ptr) {
        printf("%s\n", *ptr);
        ptr++;
    }
    return 0;
}