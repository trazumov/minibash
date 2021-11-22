NAME = minibash

CC = clang -g

LIBFT_DIR = libft/

LFAGS = -Wall -Wextra -Werror

SRC = src/main.c \
src/free.c \
src/help/strcmp.c \
src/init/init_env.c \
src/signals/signal.c \
src/init/init_shell.c \
src/execute/execute_bin.c \
src/execute/execute_cmd.c \
src/main_loop.c \
src/errors.c \
src/parser.c \
src/redirections.c \
src/tokens.c\
src/execute/execute_builtin.c\
parser/builtins/ft_cd.c\
parser/builtins/ft_echo.c\
parser/builtins/ft_env.c\
parser/builtins/ft_exit.c\
parser/builtins/ft_export.c\
parser/builtins/ft_pwd.c\
parser/builtins/ft_unset.c

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