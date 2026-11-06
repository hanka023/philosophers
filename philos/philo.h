/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/07 15:31:43 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// colors
#define RESET   "\033[0m"
#define RED		"\033[38;5;196m"
#define GREEN   "\033[38;5;47m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define PURPLE  "\033[38;5;99m"
#define MAGENTA "\033[35m"
#define WHITE   "\033[37m"
#define ORANGE  "\033[38;5;208m"
#define PINK    "\033[38;5;206m"
#define GRAY    "\033[38;5;242m"
#define L_BLUE  "\033[38;5;123m"

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_data
{
	int				num_of_philos;
	long long		time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	long long		start_time;
	int				finished;
	int				died;	
	pthread_mutex_t	died_mutex;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	mtx;
	pthread_t		thread;
	int				meals_eaten;
	int				died;
	long long		last_meal;
	int				to_eat;
	int				finish;
	t_data			*data;
}	t_philo;

/* * * * * * monitoring.c * * * * * */

void			print_death(t_data *data, int i, long long timestamp);
int				died(t_data *data, int i);
void			*m_routine(void *arg);
pthread_t		monitoring(t_data *data);

/* * * * * * routine.c * * * * * * * */

void			before_start(t_philo *philo);
void			finished(t_philo *philo);
void			one_philo(t_philo *philo);
void			*routine(void *arg);

/* * * * * * actions.c * * * * */

void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);
void			eating(t_philo *philo);

/* * * * * * conditions.c * * * * */

int				is_simulation_over(t_philo *philo);
int				simulation_over(t_data *data);
int				philo_died(t_philo *philo);

/* * * * * * philo_forking.c * * * * */

int				even(t_philo *philo);
int				odd(t_philo *philo);
int				lock_forks(t_philo *philo);
void			unlock_forks(t_philo *philo);

/* * * * print_function.c * * * */

int				philo_died(t_philo *philo);
void			print_fork(t_philo *philo);
void			print_eating(t_philo *philo);
void			print_sleeping(t_philo *philo);
void			print_thinking(t_philo *philo);

/* * * * * struct.c * * * * * */

int				ft_atoi(const char *str);
t_data			*data_to_struct(int *args, int len, pthread_mutex_t *forks);
t_philo			*philo_to_struct(t_data *data, pthread_mutex_t *forks);
void			print_data(t_data *data, int len);

/* * * * * * thread_mutex.c * * * * */

pthread_mutex_t	*mutex_init(int len);
int				mutex_destroy(pthread_mutex_t *mtx, int len, t_data *data);
pthread_t		*pthread_init(int len, t_philo *philos);
void			my_pthreads_join(pthread_t *thread, int len);
void			thread_func(t_data *data);

/* * * * * * time.c * * * * * */

long long		get_time_in_ms(void);
void			ft_usleep(long long time_in_ms, t_data *data);
long long		count_time_to_think(t_philo *philo);


/* * * * * * main_utils.c * * * * * */

int				*arg_reader(int argc, char **argv);
int				check_args(int argc, char **argv);

/* * * * * * * * * * * * * * */
