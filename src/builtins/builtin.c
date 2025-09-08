#include "nsh/nsh.h"

const builtins_t BUILTIN_TAB[] = {
    {TAG4L("cd"),      "cd",      NULL},
    {TAG4S("exit"),    "exit",    NULL},
    {TAG4S("env"),     "env",     NULL},
    {TAG4S("setenv"),  "setenv",  NULL},
    {TAG4S("unsetenv"),"unsetenv",NULL},
    {TAG4S("echo"),    "echo",    NULL},
    {TAG4S("history"), "history", NULL},
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
    {TAG4L(":"),      ":",       NULL},
    {0, NULL, NULL}
};
