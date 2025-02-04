# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbuchter <pbuchter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 11:43:52 by pbuchter          #+#    #+#              #
#    Updated: 2025/02/04 17:10:34 by pbuchter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
INCLUDES = includes

NAME = minishell
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	build_in.c build_in_direct.c build_in_echo.c build_in_env.c \
		build_in_exit.c build_in_export.c build_in_export_utils.c \
		build_in_unset.c executor.c executor_call_execve.c \
		executor_pipe_line.c executor_pipes_utils.c \
		executor_rd_heredoc.c executor_rd_utils.c executor_utils.c expander.c \
		expander_args.c expander_args_split.c expander_args_split_utils.c \
		expander_args_utils.c \
		expander_cmds.c expander_env.c expander_merge.c expander_special.c \
		main.c parser.c parser_cleaner.c parser_commands.c \
		parser_redirects_quotes.c parser_redirects_double.c \
		signal.c status_check_get_func.c \
		token_cleaner.c token_func.c tokenizer.c token_construct.c \
		token_check.c token_handle.c token_handle_quote.c token_handle_rd.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -I. -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -Ilibft -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	@rm -f $(OBJS) && echo "Cleaned *.o files"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(NAME) && echo "Cleaned *.o files and $(NAME)"

re: fclean all

.PHONY: clean fclean re all

