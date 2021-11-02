NAME = parser

SRCS = parser.c

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

