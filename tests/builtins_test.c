#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <string.h>
#include "nsh/nsh.h"
#include "lib/my_string.h"

static void redirect_all(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static const char *const TEST_ENV[] = {"USER=john", "HOME=/tmp", NULL};

static char **dup_env_for_test(const char *const *entries)
{
    size_t count = 0;
    char **copy = NULL;

    if (!entries)
        return NULL;
    while (entries[count])
        count++;
    copy = calloc(count + 1, sizeof(char *));
    cr_assert_not_null(copy);
    for (size_t i = 0; i < count; i++) {
        copy[i] = strdup(entries[i]);
        cr_assert_not_null(copy[i]);
    }
    return copy;
}

static void free_env_for_test(char **env)
{
    if (!env)
        return;
    for (size_t i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}

Test(print_arr, prints_env, .init = redirect_all)
{
    char *envp[] = {"USER=john", "HOME=/tmp", NULL};
    int status = print_arr(envp);

    fflush(stdout);
    cr_expect_eq(status, 0);
    cr_expect_stdout_eq_str("USER=john\nHOME=/tmp\n");
    cr_expect_stderr_eq_str("");
}

Test(print_arr, first_element_null)
{
    char *envp[] = {NULL};
    int status = print_arr(envp);

    cr_expect_eq(status, -1);
}

Test(print_arr, null_array)
{
    char **envp = NULL;
    int status = print_arr(envp);

    cr_expect_eq(status, -1);
}

Test(build_variable_and_value, merge)
{
    char *var = "toto";
    char *val = "titi";
    char *merged_str = build_variable_and_value(var, val);

    cr_assert_str_eq(merged_str, "toto=titi");
}

Test(build_variable_and_value, null_var)
{
    char *var = NULL;
    char *val = "titi";
    char *merged_str = build_variable_and_value(var, val);

    cr_expect_null(merged_str);
}

Test(build_variable_and_value, null_val)
{
    char *var = "toto";
    char *val = NULL;
    char *merged_str = build_variable_and_value(var, val);

    cr_assert_str_eq(merged_str, "toto=");
}

Test(add_arr_element, add_element)
{
    char **envp = calloc(3, sizeof(char *));
    char *element = strdup("toto=titi");
    char **new_array = NULL;

    cr_assert_not_null(envp);
    cr_assert_not_null(element);
    envp[0] = strdup("USER=john");
    envp[1] = strdup("HOME=/tmp");
    cr_assert_not_null(envp[0]);
    cr_assert_not_null(envp[1]);
    new_array = add_arr_element(element, envp);
    cr_assert_not_null(new_array);
    cr_assert_str_eq(new_array[0], "USER=john");
    cr_assert_str_eq(new_array[1], "HOME=/tmp");
    cr_assert_str_eq(new_array[2], "toto=titi");
    cr_assert_null(new_array[3]);
    for (size_t i = 0; new_array[i]; i++)
        free(new_array[i]);
    free(new_array);
}

Test(add_arr_element, null_element)
{
    char **envp = calloc(3, sizeof(char *));
    char *element = NULL;
    char **new_array = NULL;
    
    cr_assert_not_null(envp);
    envp[0] = strdup("USER=john");
    envp[1] = strdup("HOME=/tmp");
    cr_assert_not_null(envp[0]);
    cr_assert_not_null(envp[1]);
    new_array = add_arr_element(element, envp);
    cr_assert_not_null(new_array);
    cr_assert_str_eq(new_array[0], "USER=john");
    cr_assert_str_eq(new_array[1], "HOME=/tmp");
    cr_assert_null(new_array[2]);
    for (size_t i = 0; new_array[i]; i++)
        free(new_array[i]);
    free(new_array);
}

Test(add_arr_element, null_array)
{
    char **envp = NULL;
    char *element = strdup("toto=titi");
    char **new_array = NULL;

    cr_assert_not_null(element);
    new_array = add_arr_element(element, envp);
    cr_assert_str_eq(new_array[0], "toto=titi");
    free(element);
    free(new_array);
}

Test(build_robust_var_to_cmp, normal_test)
{
    char *var = "toto";
    char *new_var = build_robust_var_to_cmp(var);

    cr_assert_str_eq(new_var, "toto=");
}

Test(builtin_unsetenv, removes_existing_variable, .init = redirect_all)
{
    nsh_t shell = {0};
    char **av = (char *[]){"unsetenv", "USER", NULL};
    int status = 0;

    shell.env = dup_env_for_test(TEST_ENV);
    status = builtin_unsetenv(2, av, &shell);

    cr_assert_eq(status, 0);
    cr_assert_not_null(shell.env);
    cr_assert_str_eq(shell.env[0], "HOME=/tmp");
    cr_assert_null(shell.env[1]);
    cr_expect_stdout_eq_str("");
    cr_expect_stderr_eq_str("");
    free_env_for_test(shell.env);
}

Test(builtin_unsetenv, missing_argument, .init = redirect_all)
{
    nsh_t shell = {0};
    char **av = (char *[]){"unsetenv", NULL};
    int status = 0;

    shell.env = dup_env_for_test(TEST_ENV);
    status = builtin_unsetenv(1, av, &shell);

    cr_assert_eq(status, 84);
    cr_expect_stdout_eq_str("");
    cr_expect_stderr_eq_str("Too few arguments.\n");
    free_env_for_test(shell.env);
}

Test(builtin_unsetenv, variable_not_found, .init = redirect_all)
{
    nsh_t shell = {0};
    char **av = (char *[]){"unsetenv", "PATH", NULL};
    int status = 0;

    shell.env = dup_env_for_test(TEST_ENV);
    status = builtin_unsetenv(2, av, &shell);

    cr_assert_eq(status, 0);
    cr_assert_str_eq(shell.env[0], "USER=john");
    cr_assert_str_eq(shell.env[1], "HOME=/tmp");
    cr_expect_stderr_eq_str("Variable not found.\n");
    free_env_for_test(shell.env);
}

Test(builtin_unsetenv, null_environment, .init = redirect_all)
{
    nsh_t shell = {0};
    char **av = (char *[]){"unsetenv", "USER", NULL};
    int status = 0;

    shell.env = NULL;
    status = builtin_unsetenv(2, av, &shell);

    cr_assert_eq(status, -1);
    cr_expect_stdout_eq_str("");
    cr_expect_stderr_eq_str("");
}

// // Test(history_expansion, normal_test, .init = redirect_all)
// {
//     char *
// }
