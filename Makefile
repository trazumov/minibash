NAME = minibash

CC = clang -g

LIBFT_DIR = libft/

LFAGS = -Wall -Wextra -Werror

SRC = src/main.c \
src/tmp.c \
src/init/init_env.c \
src/signals/signal.c \
src/init/init_shell.c \
src/free.c

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