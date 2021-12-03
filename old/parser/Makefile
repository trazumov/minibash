NAME =	parser

SRCS =	parser.c		builtins/ft_cd.c		builtins/ft_echo.c		builtins/ft_env.c \
		builtins/ft_exit.c	builtins/ft_export.c	builtins/ft_pwd.c		builtins/ft_unset.c\
		../src/tokens.c

OBJS =	$(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OPTION = -lreadline

LIB =	libft/libft.a

RM =	rm -f

all:		$(NAME)

%.o:		%.c $(LIB)
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)		
			$(CC) $(CFLAGS) $^ -o $(NAME) $(OPTION) $(LIB)

clean:		
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

