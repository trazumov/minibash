NAME = minibash

CC = clang -g

LIBFT_DIR = libft/

LFAGS = -Wall -Wextra -Werror

SRC = src/main.c \
src/free.c \
src/help/utils.c \
src/signals/signal.c \
src/init/init_shell.c \
src/execute/execute_bin.c \
src/execute/execute_cmd.c \
src/main_loop.c \
src/test.c \
src/test2.c \
src/test3.c \
src/test_garbage.c \
src/t_pid_t.c \
src/errors.c \
src/parser/preparser.c\
src/parser/parser.c \
src/parser/quotes_handler.c\
src/parser/bucks_handler.c\
src/parser/parser_utils.c\
src/env.c\
src/redirections.c \
src/tokens.c\
src/pipes.c\
src/heredoc.c \
src/gnl.c \
src/gnl_utils.c \
src/execute/execute_builtin.c\
src/builtins/ft_cd.c\
src/builtins/ft_echo.c\
src/builtins/ft_env.c\
src/builtins/ft_exit.c\
src/builtins/ft_export.c\
src/builtins/ft_pwd.c\
src/builtins/ft_unset.c

OBJS = $(SRC:.c=.o)

TERMCAMP = -ltermcap -lreadline -lncurses
#TERMCAMP = -lreadline -lncurses

.c.o:
	$(CC) -c $< -o $(<:.c=.o)
#$(LFAGS) 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(SRC) $(TERMCAMP) -L $(LIBFT_DIR) -lft -o $(NAME)
	$(RM) $(OBJS) $(OBJB)

clean:
	$(RM) $(OBJS) $(OBJB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re