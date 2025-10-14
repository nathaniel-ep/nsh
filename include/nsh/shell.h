#ifndef NSH_SHELL_H_
#define NSH_SHELL_H_

typedef struct nsh_s {
    char *hard_input;
    char *input;
    int last_status;
    char **local_env;
    char **env;
    char *home;
    char *history_path;
} nsh_t;

nsh_t *init_shell_struct(char **env);
nsh_t *init_shell(char **env);
void destroy_shell_struct(nsh_t *shell);
void free_line(nsh_t *shell);
void leave_shell(nsh_t *shell);
#endif /* !NSH_SHELL_H_ */