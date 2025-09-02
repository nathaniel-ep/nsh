#include <stdio.h>
#include "nsh/memory.h"

void *xcalloc(size_t nmemb, size_t size)
{
    void *ptr = NULL;

    ptr = calloc(nmemb, size);
    if (!ptr) {
        perror("calloc");
        exit(84);
    }
    return ptr;
}