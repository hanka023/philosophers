# Název výsledného programu
NAME = philo


# Překladač a příznaky
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I libft -I gnl -I utils  -I fPie -g -fsanitize=address
# CFLAGS = -Wall -Wextra -Werror -I libft -I gnl -I utils  -I fPie -g 
# DBGF = -g -fsanitize=address,leak
# DBGFLAGS = -g -fsanitize=leak,address,origin

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
LDFLAGS     = -Llibft -lft 

# Seznam všech .c souborů
SRC =	main.c			\
		arguments.c 	\
		monitoring.c 	\
		routine.c		\
		struct.c		\
		thread_mutex.c 	\
		time.c 			\
		
	
# Změna koncovek .c na .o pro objekty
OBJ = $(SRC:.c=.o)

# Hlavní pravidlo
all: $(NAME)

# Jak vytvořit výsledný program z objektů
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)
# Pravidlo pro promazání objektových souborů
clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

# Pravidlo pro kompletní smazání (včetně programu)
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

# Pravidlo pro "přestavbu" od nuly
re: fclean all

.PHONY: all clean fclean re