SERVER_SRCS = src/server.c src/utils.c
CLIENT_SRCS = src/client.c src/utils.c
HEADERS = src/minitalk.h

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra -Llibft -lft

.PHONY: all libft clean fclean re

# Les cibles all, libft, server et client dépendent de leurs fichiers objets respectifs
all: libft server client
	@echo ✅ "Minitalk compiled\n"

# Compiler la bibliothèque libft
libft:
	@make -s -C libft
	@echo ✅ "Libft compiled\n"

# Compiler le serveur
server: ${SERVER_SRCS:.c=.o} libft/libft.a
	@${CC} ${CC_FLAGS} $^ -o $@ -s

# Compiler le client
client: ${CLIENT_SRCS:.c=.o} libft/libft.a
	@${CC} ${CC_FLAGS} $^ -o $@ -s

# Les fichiers objets dépendent des fichiers sources et des en-têtes correspondantes
src/server.o: src/server.c ${HEADERS}
src/utils.o: src/utils.c ${HEADERS}
src/client.o: src/client.c ${HEADERS}

# Compiler chaque fichier source individuellement en fichier objet
%.o: %.c ${HEADERS}
	@${CC} -c $< -o $@ -s

clean:
	@rm -rf ${SERVER_SRCS:.c=.o} ${CLIENT_SRCS:.c=.o}
	@make -s clean -C libft
	@echo ✅ "Minitalk cleaned\n"

fclean: clean
	@rm -rf client server
	@make -s fclean -C libft
	@echo ✅ "Libft cleaned\n"

re: fclean all

