NAME = philo


CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I gnl -I utils -I fPie
DEBUG_FLAGS = -g -fsanitize=thread
ASAN_FLAGS = -g -fsanitize=address


SRC =   philos/main.c           \
 		philos/actions.c  		\
		philos/conditions.c		\
        philos/forking.c  		\
        philos/monitoring.c     \
		philos/print_function.c \
		philos/routine.c        \
        philos/struct.c         \
        philos/thread_mutex.c   \
        philos/time.c           


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

asan: CFLAGS += -g -fsanitize=address -fsanitize=leak
asan: re

.PHONY: all clean fclean re debug asan