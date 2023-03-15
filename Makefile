CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME_CLIENT = client
NAME_SERVER = server
LIBFT = ./libft/libft.a

SRC_CLIENT = src/client.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

SRC_SERVER = src/server.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)

NAME_CLIENT_BONUS = client_bonus
BONUS_SRC_CLIENT = bonus/client_bonus.c
BONUS_OBJ_CLIENT = $(BONUS_SRC_CLIENT:.c=.o)

NAME_SERVER_BONUS = server_bonus
BONUS_SRC_SERVER = bonus/server_bonus.c
BONUS_OBJ_SERVER = $(BONUS_SRC_SERVER:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(OBJ_CLIENT): $(SRC_CLIENT)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_SERVER): $(SRC_SERVER)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_CLIENT): $(BONUS_SRC_CLIENT)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_SERVER): $(BONUS_SRC_SERVER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(MAKE) --no-print-directory -C ./libft
	$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

$(NAME_SERVER): $(OBJ_SERVER)
	$(MAKE) --no-print-directory -C ./libft
	$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

$(NAME_CLIENT_BONUS): $(BONUS_OBJ_CLIENT)
	$(MAKE) --no-print-directory -C ./libft
	$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

$(NAME_SERVER_BONUS): $(BONUS_OBJ_SERVER)
	$(MAKE) --no-print-directory -C ./libft
	$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

clean:
	$(MAKE) clean -C ./libft
	rm -rf $(OBJ_CLIENT) $(OBJ_SERVER)
	rm -rf $(BONUS_OBJ_CLIENT) $(BONUS_OBJ_SERVER)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME_CLIENT) $(NAME_SERVER)
	rm -rf $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re: fclean all

.PHONY: all clean fclean re

.SUFFIXES: .c .o
