# Název výsledného programu
NAME = philo


# Překladač a příznaky
CC = cc

CFLAGS = -Wall -Wextra -Werror -I libft -I gnl -I utils  -I fPie 
DEBUG_FLAGS = -g -fsanitize=thread
ASAN_FLAGS = -g -fsanitize=address

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
LDFLAGS     = -Llibft -lft 

# Seznam všech .c souborů
SRC =	philos/main.c			\
		philos/monitoring.c 	\
		philos/routine.c		\
		philos/philo_actions.c \
		philos/philo_forking.c \
		philos/struct.c		\
		philos/thread_mutex.c 	\
		philos/time.c 			
		
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

# Pravidlo pro debug: přenastaví CFLAGS na DEBUG_FLAGS a znovu zkompiluje
debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

asan: CFLAGS += -g -fsanitize=address -fsanitize=leak
asan: re

.PHONY: all clean fclean re debug asan

