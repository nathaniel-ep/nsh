#include <stdio.h>
#include "nsh/nsh.h"
#include "lib/my_string.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int builtin_env(MU int ac, MU char **av, nsh_t *shell)
{
    char **env = shell->env;

    print_arr(env);
    return 0;
}

bool check_variable_name(char *var)
{
    if (!isalpha(*var)) {
        dprintf(2, "Variable must start with an alphabetic character.\n");
        return false;
    }
    while (var && *var) {
        if (!isalnum(*var)) {
            dprintf(2, "Variable must contain only alphanumeric characters.\n");
            return false;
        }
        var++;
    }
    return true;
}

char *build_variable_and_value(char *var, char *val)
{
    char *merged_str = NULL;
    char *ptr = NULL;
    size_t size = 0;

    if (!var || !check_variable_name(var))
        return NULL;
    merged_str = xcalloc(strlen(var) + (val ? strlen(val) : 0) + 2, sizeof(char));
    ptr = merged_str;
    size = strlen(var);
    memcpy(ptr, var, size * sizeof(char));
    ptr += size;
    memcpy(ptr, "=", 1 * sizeof(char));
    if (!val)
        return merged_str;
    ptr += 1;
    size = strlen(val);
    memcpy(ptr, val, size * sizeof(char));
    ptr += size;
    *ptr = '\0';

    return merged_str;
}

int builtin_setenv(int ac, char **av, nsh_t *shell)
{
    char *new_element = NULL;
    char **env = shell->env;

    if (ac == 1)
    {
        builtin_env(ac, av, shell);
        return 0;
    }
    if (ac > 3)
    {
        dprintf(2, "Too many arguments.\n");
        return 84;
    }
    new_element = build_variable_and_value(av[1], av[2]);
    if (!new_element)
        return 84;
    shell->env = add_arr_element(new_element, env);
    return 0;
}

char *build_robust_var_to_cmp(char *var)
{
    char *new_var = NULL;
    char *ptr = NULL;
    size_t size = 0;

    if (!var)
        return NULL;
    new_var = xcalloc(strlen(var) + 2, sizeof(char));
    ptr = new_var;
    size = strlen(var);
    memcpy(ptr, var, size * sizeof(char));
    ptr += size;
    memcpy(ptr, "=", 1 * sizeof(char));
    ptr++;
    *ptr = 0;
    return new_var; 
}

int builtin_unsetenv(int ac, char **av, nsh_t *shell)
{
    char **env = shell->env;
    char *new_var = NULL;
    void *ptr = env;

    if (!env || !(*env))
        return -1;
    if (ac == 1) {
        dprintf(2, "Too few arguments.\n");
        return 84;
    }
    for (int i = 1; av[i]; i++) {
        new_var = build_robust_var_to_cmp(av[i]);\
        env = remove_arr_element(new_var, env);
        if (ptr == env)
            dprintf(2, "Variable not found.\n");
        ptr = env;
        free(new_var);
    }
    shell->env = env;
    return 0;
}