CC:= cc
NAME:= minishell
GFLAGS:= -Wall -Werror -Wextra -g
FILES:= main.c
OBJ_FILES:= ${FILES:.c=.o}
LIB:= -lreadline

all: ${NAME}

${NAME}: ${OBJ_FILES}

test:
	cc *.c -I. -Ilibft -Llibft -lft -lreadline  -fdiagnostics-color=always && ./a.out
