#include "nsh/nsh.h"

const builtins_t BUILTIN_TAB[] = {
    {TAG4L("cd"),      "cd",      NULL},
    {TAG4S("exit"),    "exit",    &builtin_exit},
    {TAG4S("env"),     "env",     &builtin_env},
    {TAG4S("setenv"),  "setenv",  &builtin_setenv},
    {TAG4S("unsetenv"),"unsetenv",&builtin_unsetenv},
    {TAG4S("echo"),    "echo",    NULL},
    {TAG4S("history"), "history", &builtin_history},
    {TAG4S("set"),     "set",     NULL},
    {TAG4S("unset"),   "unset",   NULL},
    {TAG4S("which"),   "which",   NULL},
    {TAG4S("where"),   "where",   NULL},
    {TAG4S("repeat"),  "repeat",  NULL},
    {TAG4L("fg"),      "fg",      NULL},
    {TAG4L("bg"),      "bg",      NULL},
    {TAG4S("jobs"),    "jobs",    NULL},
    {TAG4S("type"),    "type",    NULL},
    {TAG4S("alias"),   "alias",   NULL},
    {TAG4S("unalias"), "unalias", NULL},
    {TAG4S("exec"),    "exec",    NULL},
    {TAG4L(":"),      ":",       &builtin_colon},
    {0, NULL, NULL}
};
