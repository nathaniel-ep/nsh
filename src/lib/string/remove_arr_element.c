#include <stddef.h>
#include <stdio.h>
#include "lib/memory.h"
#include <string.h>
#include <stdbool.h>

void *remove_arr_element(void *element, void *arr)
{
    void **tmp = arr;
    void **ptr = NULL;
    int count = 0;
    void *savior = NULL;
    bool found = false;

    if (!element || !tmp || !(*tmp))
        return arr;
    while (tmp && *tmp) {
        if (!strncmp(element, *tmp, strlen(element)))
            found = true;
        tmp++;
        count++;
    }
    if (!found)
        return arr;
    tmp = arr;
    ptr = xcalloc(count, sizeof(void *));
    savior = ptr;
    while (tmp && *tmp) {
        if (!strncmp(element, *tmp, strlen(element))) {
            free(*tmp);
            tmp++;
            continue;
        }
        *ptr = xstrdup(*tmp);
        free(*tmp);
        tmp++;
        ptr++;
    }
    *ptr = NULL;
    free(arr);
    return savior;
}