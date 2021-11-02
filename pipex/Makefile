NAME =		pipex

SRCS =		pipex.c		utils.c

SRCS_B =	bonus/get_next_line_bonus.c		bonus/get_next_line_utils_bonus.c		bonus/heredoc_bonus.c\
			bonus/pipex_bonus.c				bonus/utils_bonus.c

OBJS =		$(SRCS:.c=.o)

OBJS_B =	$(SRCS_B:.c=.o)

RM =		rm -f

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror

LIB =		libft/libft.a

all:		$(NAME)

%.o:		%.c $(LIB)
			$(CC) $(CFLAGS) -c $< -o $@

$(LIB):		
			make -C libft

$(NAME):	$(OBJS)		
			$(CC) $(CFLAGS) $^ -o $(NAME) $(LIB)

bonus:		$(OBJS_B)
			$(CC) $(CFLAGS) $^ -o $(NAME) $(LIB)

clean:		
			$(RM) $(OBJS) $(OBJS_B)
			make clean -C libft

fclean:		clean
			$(RM) $(NAME)
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re bonus