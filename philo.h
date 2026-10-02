# include <stdio.h>
# include <unistd.h> 
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_data{
	int num_of_philos;
	size_t time_to_die;
	size_t time_to_eat;
	size_t time_to_sleep;
	size_t must_eat;
	t_philo *philos;
	int		died;	
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
pthread_mutex_t	mtx;
t_data			*data;
int				died;
} t_philo;

/* * * * * arguments.c * * * * */

t_data		*data_to_struct(int *arguments, int len, pthread_mutex_t *forks);
t_philo		*philo_to_struct(t_data *data, pthread_mutex_t *forks);
int			*arg_reader(int argc, char **argv);
void		print_data(t_data *data, int len);

/* * * * * * philo.c   -thread_mutex.c* * * * * */

void			*routine(void *arg);
pthread_mutex_t	*mutex_init(int len);
pthread_t		*pthread_init(int len, t_philo *philos);
void			my_pthreads_join(pthread_t *thread, int len);
int				mutex_destroy(pthread_mutex_t *mtx, int len);

/* * * * * * time.c * * * * * */

long long	get_time_in_ms (void);
void		ft_usleep (long long time_in_ms);

/* * * * * * monitoring.c * * * * * */

void	*m_routine(void *arg);
//int		monitoring (t_data *data);  
pthread_t monitoring (t_data *data);

/* * * * * * * * * * * * * * */


