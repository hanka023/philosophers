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
pthread_t t1;
pthread_t t2;

pthread_mutex_init(&lock, NULL);

pthread_create(&t1, NULL, &routine,"Hello world\n");
pthread_create(&t2, NULL, &routine, NULL);


pthread_join(pthread_self(), NULL);


pthread_join(t1, NULL);
pthread_join(t2, NULL);

pthread_mutex_destroy(&lock);

printf("count: %d\n", cont);
}

// main(int argc, char *argv[])
// {
// pthread_t t1;
// void *res;
// int s;
// s = pthread_create(&t1, NULL, &routine, "Hello world\n");
// if (s != 0)
// errExitEN(s, "pthread_create");
// printf("Message from main()\n");
// s = pthread_join(t1, &res);
// if (s != 0)
// errExitEN(s, "pthread_join");
// printf("Thread returned %ld\n", (long) res);
// //exit(EXIT_SUCCESS);
// }


#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    pthread_t tid = pthread_self();

    // 1. Ochrana: Jak zabránit zavolání join na sebe sama
    if (pthread_equal(tid, pthread_self())) {
        printf("Nemohu zavolat pthread_join na sebe sama!\n");
    } else {
        pthread_join(tid, NULL);
    }

    // 2. Test, co se stane na Linuxu, když to přesto uděláme:
    int s = pthread_join(pthread_self(), NULL);
    if (s != 0) {
        printf("pthread_join selhal s chybou %d: %s\n", s, strerror(s));
        // Na Linuxu vrátí chybu EDEADLK (Resource deadlock avoided)
    }

    return 0;
}