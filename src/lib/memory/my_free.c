#include <string.h>
#include "lib/memory.h"

void my_free(void *ptr)
{
    if (!ptr)
        return;
    free(ptr);
}