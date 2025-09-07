// env.h - Environment management (variables, PATH resolution)
#ifndef NSH_ENV_H
    #define NSH_ENV_H

char **dup_env(char **env);
char *get_home(void);
#endif // NSH_ENV_H
