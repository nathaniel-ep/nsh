CC = gcc
NAME = nsh
SRC = $(shell find src -name '*.c' ! -name 'main.c')
OBJ = $(SRC:.c=.o)
MAIN = src/main.c
MAIN_OBJ = $(MAIN:.c=.o)

# Flags
CPPFLAGS := -Iinclude
CFLAGS = -Werror -Wall -Wextra -O2
LDFLAGS :=
LDLIBS := -lreadline
DEBUGFLAGS = -g3 -ggdb
TOBJ = *.gc*

.PHONY: all clean fclean re debug val tests_run cvrg style

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(MAIN_OBJ) -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f src/*.d
	rm -f src/*.o
	rm -f $(OBJ)
	rm -f $(OBJ:.o=.d)
	rm -f $(TOBJ)
	rm -f unit_tests
fclean: clean
	rm -f $(NAME)
re: fclean all

debug: CFLAGS += $(DEBUGFLAGS)
debug: re

val: CFLAGS += $(DEBUGFLAGS)
val: re
	valgrind --leak-check=full --show-leak-kinds=definite,indirect,possible --errors-for-leak-kinds=definite,indirect --track-origins=yes ./$(NAME)
tests_run: CFLAGS += --coverage
tests_run:
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) tests/*.c -o unit_tests $(LDFLAGS) -lcriterion $(LDLIBS)
	./unit_tests
cvrg:
	gcovr --exclude tests/
style: fclean
	coding-style .
	cat *.log
	rm -f *.log

-include $(OBJ:.o=.d)
