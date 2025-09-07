// memory.h - Memory management helpers (arenas, pools)
#ifndef NSH_MEMORY_H
    #define NSH_MEMORY_H
    #include <stdlib.h>

void *xcalloc(size_t nmemb, size_t size);
void my_free(void *ptr);
char *xstrdup(char *src);
#endif // NSH_MEMORY_H
