// nsh.h - Central project header
#ifndef NSH_NSH_H
#define NSH_NSH_H

#include "lib/memory.h"
#include "nsh/env.h"
#include "nsh/signal.h"
#include "nsh/term.h"
#include "nsh/history.h"
#include "nsh/lexer.h"
#include "nsh/parser.h"
#include "nsh/ast.h"
#include "nsh/expansion.h"
#include "nsh/redirection.h"
#include "nsh/exec.h"
#include "nsh/job_control.h"
#include "nsh/builtins.h"
#include "nsh/io.h"
#include "nsh/utils.h"
#include "shell.h"
#define MU __attribute_maybe_unused__

#endif // NSH_NSH_H
