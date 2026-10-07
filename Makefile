# Název výsledného programu
NAME = philo

# Překladač a příznaky
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I gnl -I utils -I fPie
DEBUG_FLAGS = -g -fsanitize=thread
ASAN_FLAGS = -g -fsanitize=address

# Seznam všech .c souborů
SRC =   philos/main.c           \
        philos/monitoring.c     \
        philos/routine.c        \
        philos/philo_actions.c  \
        philos/philo_forking.c  \
		philos/print_function.c \
        philos/struct.c         \
        philos/thread_mutex.c   \
        philos/time.c           

# Změna koncovek .c na .o pro objekty
OBJ = $(SRC:.c=.o)

# Hlavní pravidlo
all: $(NAME)

# Jak vytvořit výsledný program z objektů
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Pravidlo pro kompilaci jednotlivých .c souborů na .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pravidlo pro promazání objektových souborů
clean:
	rm -f $(OBJ)

# Pravidlo pro kompletní smazání (včetně programu)
fclean: clean
	rm -f $(NAME)

# Pravidlo pro "přestavbu" od nuly
re: fclean all

# Pravidlo pro debug s ThreadSanitizerem
debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

# Pravidlo pro debug s AddressSanitizerem
asan: CFLAGS += -g -fsanitize=address -fsanitize=leak
asan: re

.PHONY: all clean fclean re debug asan