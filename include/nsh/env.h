// env.h - Environment management (variables, PATH resolution)
#ifndef NSH_ENV_H
    #define NSH_ENV_H

char **dup_env(char **env);
char *get_home(void);
char *build_variable_and_value(char *var, char *val);
char *build_robust_var_to_cmp(char *var);
#endif // NSH_ENV_H
