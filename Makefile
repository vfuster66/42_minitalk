SERVER_SRCS = src/server.c utils.c
CLIENT_SRCS = src/client.c utils.c
HEADERS = src/minitalk.h

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra -Llibft -lft

%.o: %.c ${HEADERS}
	${CC} -c $< -o $@

all: libft server client

libft:
	@make -C libft

server: ${SERVER_SRCS:.c=.o} ${HEADERS} libft/libft.a
	${CC} ${SERVER_SRCS:.c=.o} ${CC_FLAGS} -o server

client: ${CLIENT_SRCS:.c=.o} ${HEADERS} libft/libft.a
	${CC} ${CLIENT_SRCS:.c=.o} ${CC_FLAGS} -o client

clean:
	rm -rf ${SERVER_SRCS:.c=.o} ${CLIENT_SRCS:.c=.o}
	@make clean -C libft

fclean: clean
	rm -rf client server
	@make fclean -C libft

re: fclean all

.PHONY: all libft clean fclean re

