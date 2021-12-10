NAME =		minishell

SRCS =		src/main/main.c			src/main/init_shell.c			src/main/main_loop.c\
			src/main/t_pid_t.c		src/main/env.c					src/main/tokens.c\
			src/parser/parser.c		src/parser/preparser.c			src/parser/quotes_handler.c\
			src/help/utils.c		src/parser/parser_utils.c		src/help/gnl_utils.c\
			src/help/free.c			src/parser/bucks_handler.c		src/help/errors.c \
			src/help/gnl.c			src/signals/signal.c			src/execute/execute_bin.c\
			src/builtins/ft_env.c	src/execute/execute_builtin.c	src/pipes/first_mid_pipes.c\
			src/pipes/pipes.c		src/pipes/execute_pipe.c		src/redirections/redirect_heredoc.c\
			src/builtins/ft_cd.c	src/builtins/ft_echo.c			src/redirections/redirections.c\
			src/builtins/ft_pwd.c	src/execute/execute_cmd.c		src/redirections/redirect_out.c\
			src/builtins/ft_exit.c	src/builtins/ft_export.c		src/builtins/ft_unset.c\
			src/pipes/io.c			src/redirections/redirect.c

OBJS =		$(SRCS:.c=.o)

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror

HEAD_DIR =	includes

HEADER =	$(HEAD_DIR)/minishell.h

LIBFT_DIR =	libft

LIBFT =		$(LIBFT_DIR)/libft.a

RM =		rm -f

RDL_FLAGS =	-lreadline

all:		subsystem $(NAME)

%.o:		%.c $(HEADER) $(LIBFT)
			$(CC) $(CFLAGS) -I $(HEAD_DIR) -I $(LIBFT_DIR) -c $< -o $@

subsystem:
			make -C $(LIBFT_DIR)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ $(RDL_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

clean:
			$(RM) $(OBJS)
			make clean -C $(LIBFT_DIR)

fclean:		clean
			$(RM) $(NAME)
			make fclean -C $(LIBFT_DIR)

re:			fclean all

.PHONY:		all clean fclean re