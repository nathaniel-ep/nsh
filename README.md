# nsh

A small, educational Unix shell written in C. It is inspired by Bash, but aims to be simple, modular, and easy to read. The codebase is organized into clear subsystems (lexer, parser/AST, expansion, execution, job control, builtins, etc.) so each part can be developed and tested independently.

Status: early scaffolding — the project builds and the module layout is in place; the interactive loop and features are added progressively.

## Goals

- Minimal, readable implementation focused on learning and maintainability
- Modular architecture with clear boundaries between subsystems
- Solid error handling and testability
- Compatibility with common Unix environments

## Project Layout

```
include/nsh/        Public headers (one per module)
  ├─ nsh.h          Central aggregator header
  ├─ env.h          Environment variables, PATH lookup
  ├─ memory.h       Memory helpers/allocators
  ├─ signal.h       Signals (SIGINT, SIGCHLD)
  ├─ term.h         Terminal/TTY setup
  ├─ history.h      Command history integration
  ├─ lexer.h        Tokenization
  ├─ parser.h       Parser front-end
  ├─ ast.h          AST node types/helpers
  ├─ expansion.h    Param/word expansion, globbing
  ├─ redirection.h  Redirections, pipes, here-docs
  ├─ exec.h         Execution engine
  ├─ job_control.h  Foreground/background job control
  ├─ builtins.h     Built-in commands
  ├─ io.h           Low-level I/O utilities
  └─ utils.h        Misc helpers

src/
  ├─ main.c
  ├─ env/           env.c
  ├─ memory/        memory.c
  ├─ signal/        signal.c
  ├─ term/          term.c
  ├─ history/       history.c
  ├─ lexer/         lexer.c
  ├─ parser/        parser.c
  ├─ ast/           ast.c
  ├─ expansion/     expansion.c
  ├─ redirection/   redirection.c
  ├─ exec/          exec.c
  ├─ job_control/   job_control.c
  ├─ builtins/      builtins.c
  ├─ io/            io.c
  └─ utils/         utils.c
```

## Build

Requirements

- gcc or clang, make
- readline development package (for history/line‑editing):
  - Debian/Ubuntu: `sudo apt-get install build-essential libreadline-dev`
  - Fedora: `sudo dnf install readline-devel`
- Optional (tests): Criterion unit test framework (`libcriterion-dev`) and `gcovr` for coverage

Commands

- Build: `make`
- Rebuild from scratch: `make re`
- Clean objects: `make clean` (and binary with `make fclean`)
- Debug build flags: `make debug` or `make val` (adds `-g3 -ggdb`)
- Run tests (when tests exist): `make tests_run`
- Coverage report (after tests): `make cvrg`

Output binary: `./nsh`

Note: On macOS, you may need to point to Homebrew’s readline, e.g.
`CPPFLAGS=-I$(brew --prefix readline)/include LDFLAGS=-L$(brew --prefix readline)/lib make`

## Roadmap (High Level)

- REPL loop using `readline()` with history
- Lexer: words, quotes, operators, expansions markers
- Parser + AST: command, pipeline, lists, control operators
- Expansion: variables, command substitution (later), globbing
- Redirections: > >> < <<, pipelines
- Execution: builtins vs. external commands, PATH resolution
- Job control: foreground/background, signals, process groups
- Builtins (initial set): `echo`, `cd`, `pwd`, `exit`, `env`, `export`, `unset`
- Error handling & diagnostics
- Tests for each module (Criterion)

## Development Notes

- Style: warnings as errors (`-Wall -Wextra -Werror`), 80‑column ruler configured in VS Code
- Headers live under `include/` and are included as `#include "nsh/<name>.h"`
- Keep modules independent; expose only what’s needed in headers
- Prefer small, focused functions; handle errors explicitly

## Testing

`make tests_run` compiles and runs unit tests when a test suite is present under `tests/` (example entry file: `tests/42sh_test.c`). Add more test files as the modules evolve. For coverage, run `make cvrg` after tests.

## License

This project is released under the terms in `LICENSE`.
