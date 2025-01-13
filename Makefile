CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = includes

NAME = minishell
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	parser.c tokenizer.c token_handle.c parser_helpers.c parser_cleaning.c main.c

OBJS = $(SRCS:.c=.o)

TEST_PROMPT = "ls | cat > OUT < IN"

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -I. -Ilibft -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -I$(INCLUDES) -Ilibft -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all

t: $(LIBFT)
	clear
	cc *.c -I${INCLUDES} -Ilibft -Llibft -lft -lreadline -g && ./a.out ${TEST_PROMPT}

leak: $(LIBFT)
	cc *.c -I${INCLUDES} -Ilibft -Llibft -lft -lreadline -g
	valgrind --leak-check=full ./a.out ${TEST_PROMPT}
