#ifndef NSH_SHELL_H_
#define NSH_SHELL_H_

#endif /* !SHELL_H_ */


typedef struct nsh_s {
    char *hard_input;
    char *input;
    int last_status;
    char **local_env;
    char **env;
} nsh_t;

nsh_t *init_shell_struct(char **env);
void destroy_shell_struct(nsh_t *shell);