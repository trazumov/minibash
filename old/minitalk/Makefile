SERVER = server

CLIENT = client

CC = gcc

FLAGS = -Wall -Wextra -Werror

LIBFT = libft.a

all : $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT) :
	make -C libft

$(CLIENT) : client.o minitalk.h
	$(CC) $(FLAGS) client.c libft/libft.a -o $(CLIENT)

$(SERVER): server.o functions.o minitalk.h
	$(CC) $(FLAGS) server.c functions.c libft/libft.a -o $(SERVER)
	
clean :
	make clean -C libft
	rm -rf client.o server.o functions.o

fclean : clean
	make fclean -C libft
	rm -rf $(SERVER) $(CLIENT)

re : fclean all

.PHONY: all clean fclean re
