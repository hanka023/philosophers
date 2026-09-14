# include <stdio.h>
# include <unistd.h> 
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"


typedef struct s_data{
	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat;
}t_data;


typedef struct s_philo{
int 			id;
pthread_t 		thread;
int				meals_eaten;
size_t			last_meal;
size_t			time_to_die;
size_t			time_to_eat;
size_t			time_to_sleep;
int				num_to_eat;
int				*dead;
pthread_mutex_t	*left_fork;
pthread_mutex_t	*right_fork;
pthread_mutex_t	*write_lock;
t_data			*data;
} t_philo;



/* * * * * arguments.c * * * * */

t_data		*data_to_struct(int *arguments, int len);
t_philo		*philo_to_struct(int len, t_data *data, pthread_mutex_t *forks);
int			*arg_reader(int argc, char **argv);
void		print_data(t_data *data, int len);

/* * * * * * philo.c * * * * * */


void			*routine (void *arg);
pthread_mutex_t	*mutex_init(int len);
pthread_t		*pthread_init(int len, t_philo *philos);
void			my_pthreads_join(pthread_t *thread, int len);


/* * * * * * time.c * * * * * */

long long	get_time_in_ms (void);
void		ft_usleep (size_t time_in_ms);

/* * * * * * * * * * * * * * */

