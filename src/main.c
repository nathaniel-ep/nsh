#include <unistd.h>
#include <readline/readline.h>
#include "nsh/nsh.h"

int main(void)
{
    char *input = NULL;

    input = readline("$> ");
    while (input)
    {
        printf("you writed: %s\n", input);
        input = readline("$> ");
    }

    return 0;
}
