#include <string.h>
#include "nsh/memory.h"

void my_free(void *ptr)
{
    if (!ptr)
        return;
    free(ptr);
}