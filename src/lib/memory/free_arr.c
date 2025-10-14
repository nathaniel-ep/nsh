#include <stdlib.h>

void free_arr(void **ptr)
{
    if (!ptr)
        return;
    while (ptr && *ptr) {
        free(*ptr);
    }
    free(ptr);
}