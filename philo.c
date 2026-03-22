#include <stdio.h>
#include <unistd.h> 
#include <pthread.h>


typedef struct s_philo{
int 			id;
pthread_t 		thread;
int				meals_eaten;
size_t			last_meal;
size_t			time_to_die;
size_t			time_to_eat;
size_t			time_to_sleep;
int				num_times_to_eat;
int				*dead;
pthread_mutex_t	*left_fork;
pthread_mutex_t	*right_fork;
pthread_mutex_t	*write_lock;
} t_philo;



int cont = 0;
pthread_mutex_t lock;

void  *routine()
{
  int i;

  i = -1;
  
  while (++i < 1000000)
  {
		pthread_mutex_lock(&lock);
        cont++;
        pthread_mutex_unlock(&lock);

  }
  
  return (NULL);
}

int main()
{
  pthread_t tid1, tid2;

 pthread_mutex_init(&lock, NULL);

  pthread_create(&tid1, NULL, &routine, NULL);
  pthread_create(&tid2, NULL, &routine, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

 pthread_mutex_destroy(&lock);

 printf("count: %d\n", cont);
}
