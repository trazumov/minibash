NAME = minibash

CC = clang $(FLAGS)

FLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft/

LFAGS = -Wall -Wextra -Werror

SRC = src/main/main.c \
src/help/free.c \
src/help/utils.c \
src/signals/signal.c \
src/main/init_shell.c \
src/execute/execute_bin.c \
src/execute/execute_cmd.c \
src/main/main_loop.c \
src/main/t_pid_t.c \
src/help/errors.c \
src/parser/preparser.c\
src/parser/parser.c \
src/parser/quotes_handler.c\
src/parser/bucks_handler.c\
src/parser/parser_utils.c\
src/main/env.c\
src/redirections/redirections.c \
src/redirections/redirect_out.c \
src/redirections/redirect_heredoc.c \
src/main/tokens.c\
src/pipes/pipes.c\
src/pipes/execute_pipe.c\
src/pipes/first_mid_pipes.c\
src/help/gnl.c \
src/help/gnl_utils.c \
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