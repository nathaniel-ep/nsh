#include <stddef.h>
#include <stdio.h>
#include "lib/memory.h"

void *add_arr_element(void *element, void *arr)
{
    void **tmp = arr;
    void **ptr = NULL;
    int count = 0;
    void *savior = NULL;

    if (!element)
    return arr;
    while (tmp && *tmp) {
        tmp++;
        count++;
    }
    tmp = arr;
    ptr = xcalloc(count + 2, sizeof(void *));
    savior = ptr;
    while (tmp && *tmp) {
        *ptr = xstrdup(*tmp);
        free(*tmp);
        tmp++;
        ptr++;
    }
    *ptr = element;
    ptr++;
    *ptr = NULL;
    free(arr);
    return savior;
}