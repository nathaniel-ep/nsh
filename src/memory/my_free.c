#include <string.h>
#include "nsh/memory.h"

void my_free(void *ptr, size_t size)
{
    if (!ptr)
        return;
    memset(ptr, 0, size);
    free(ptr);
}