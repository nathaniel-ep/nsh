#include <unistd.h>
#include <errno.h>
#include <readline/history.h>
#include "nsh/nsh.h"

void dump_history(int n)
{
    HIST_ENTRY **list = NULL;
    HIST_ENTRY *e = NULL;
    int start = n == -1 ? 0 : history_length - n;

    list = history_list();
    if (!list)
        return;
    for (int i = start; i < history_length; i++) {
        e = history_get(history_base + i);
        if (e) {
            printf("%d  %s\n", history_base + i, e->line);
        }
    }
}

void history_print_help(FILE *std)
{
    fprintf(std,
        "Usage: history [options] [numeric_value]\n"
        "\n"
        "Options:\n"
        "  -h                Show this help message\n"
        "  -c                Clear the history list\n"
        "  -d <position>     Delete the entry at the given position\n"
        "  -r <file>         Read history entries from <file>\n"
        "  -w <file>         Write current history entries to <file>\n"
        "\n"
        "Arguments:\n"
        "  numeric_value     Display the last N history entries\n"
        "\n"
        "Examples:\n"
        "  history           Show full history\n"
        "  history 10        Show last 10 entries\n"
        "  history -d 3      Delete entry number 3\n"
        "  history -r file   Read entries from file\n"
        "  history -w file   Write entries to file\n"
        "  history -c        Clear all history\n"
    );
}

int history_delete_pos(const char *arg)
{
    char *end = NULL;
    long pos = 0;
    
    errno = 0;
    pos = strtol(arg, &end, 10);
    if (errno || pos <= 0) {
        fprintf(stderr, "nsh: history: invalid position\n");
        return 2;
    }
    long idx = pos - history_base;
    if (idx < 0 || idx >= history_length) {
        fprintf(stderr, "nsh: history: position out of range\n");
        return 2;
    }
    HIST_ENTRY *e = remove_history((int)idx);
    if (!e) {
        fprintf(stderr, "nsh: history: failed to remove entry\n");
        return 1;
    }
    free_history_entry(e);
    return 0;
}

int builtin_history(int ac, MU char **av, MU nsh_t *shell)
{
    char *end = NULL;
    int n = 0;
    
    errno = 0;
    if (ac < 2) {
        dump_history(0);
        return 0;
    }
    if (make_history_flag_tag(av[1]) == HISTORY_FLAG_H) {
        history_print_help(stderr);
        return 0;
    }
    if (make_history_flag_tag(av[1]) == HISTORY_FLAG_C) {
        clear_history();
        write_history(shell->history_path);
        return 0; 
    }
    if (make_history_flag_tag(av[1]) == HISTORY_FLAG_D) {
        if (ac < 3)
            return 2;
        return history_delete_pos(av[2]);
    }
    if (make_history_flag_tag(av[1]) == HISTORY_FLAG_R) {
        if (ac < 3)
            return 2;
        read_history(av[2]);
        return errno;
    }
    if (make_history_flag_tag(av[1]) == HISTORY_FLAG_W) {
        if (ac < 3)
            return 2;
        write_history(av[2]);
        return errno;
    }
    n = strtol(av[1], &end, 10);
    if (errno || *end || n <= 0) {
        fprintf(stderr, "nsh: history: %s: a not null numeric argument required\n", av[1]);
        return 2;
    }
    dump_history(n);
    return 0;
}