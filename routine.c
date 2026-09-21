# include "philo.h"
#include <stdio.h>
// int check()
// {

// }

void *routine (void *arg)
{
	t_philo *philo;
	long long time;

	philo = (t_philo *)arg;

	time = get_time_in_ms();
	if (!philo)
    {
        printf("CHYBA: philo je NULL!\n");
        return (NULL);
    }
    if (!philo->data)
    {
        printf("CHYBA: philo->data je NULL!\n");
        return (NULL);
    }
	if (philo->data->num_of_philos == 1)
    {
        // // 1. Vezme svou jedinou vidličku
        // pthread_mutex_lock(philo->left_fork);
        // printf( "philo has taken a fork");

        // // 2. Čeká, dokud nezemře (čekání nastavené na čas do smrti)
        // usleep(philo->time_to_die);

        // // 3. Odemkne vidličku a ukončí vlákno
        // pthread_mutex_unlock(philo->left_fork);
        return 0 ;
    }
	//printf (" ----------------------- time %lld --------------------\n", time);

	//printf (" ----------------------- philo -> last_meal get time in ms %lld --------------------\n", get_time_in_ms());
	//printf (" ----------------------- philo -> last_meal  --- ph last meal %ld --------------------\n", philo -> last_meal);
	//(philo -> last_meal) = time;
	//printf (" ----------------------- philo -> last_meal   -- time %lld --------------------\n", time);
	
	if ((philo -> id) %2 != 0)
		ft_usleep(2);
	
	if (philo -> id == 1)
		ft_usleep (2000);
	(philo -> last_meal) = get_time_in_ms ();
	while (1)
	{
	//	ft_usleep(111);
	//	printf ("test casu  * * * %lld * * *%lld \n", time,  get_time_in_ms() );
	//	printf("philo %d start * * * %lld * * *\n", (philo -> id),  get_time_in_ms());
	//	fflush(stdout);
	
		if ((philo -> meals_eaten) >= (philo -> num_to_eat))
		{
			printf("philo %d is finished xxx\n", philo -> id);
			fflush(stdout);
			break;
		}
		if (philo -> data -> died == 1)
		{
			printf ("philo %d chcipnul * * * %lld * * *%lld \n", philo -> id, time,  get_time_in_ms() );
			fflush(stdout);
			break;
		}

			
		if (philo -> id %2 == 0)
		{
			pthread_mutex_lock(philo -> right_fork);
			printf("philo %d has taken right fork\n", philo -> id);
			fflush(stdout);
			ft_usleep(1);

			pthread_mutex_lock(philo -> left_fork);
			printf("philo %d has taken left fork\n", philo -> id);
			fflush(stdout);
		}
		else
		{
			pthread_mutex_lock(philo -> left_fork);
			printf("philo %d has taken left fork\n", philo -> id);
			fflush(stdout);
			ft_usleep(1);
			pthread_mutex_lock(philo -> right_fork);
			printf("philo %d has taken right fork\n", philo -> id);
			fflush(stdout);
		}

		if (philo -> data -> died == 1)
		{
			fflush(stdout);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			printf ("philo %d vratil vidlicky a chcipnul * * * %lld * * * \n", philo -> id, time);
			fflush(stdout);
			break;
		}
		printf ("philo %d is eating\n", philo -> id);
		fflush(stdout);
		//printf ("x x x philo %ld last meal ------- puvodni hodnota\n", philo -> last_meal);
		//fflush(stdout);
		ft_usleep(111);
		(philo -> last_meal) = get_time_in_ms ();
		//printf ("x x x philo %ld last meal --------nova hodnota\n", philo -> last_meal);
		//fflush(stdout);
		(philo -> meals_eaten) ++;
		printf ("philo %d meals eaten: %d\n", philo -> id, philo -> meals_eaten);
		fflush(stdout);
		ft_usleep(philo -> time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		printf("philo %d vratil right fork\n", philo -> id);
		fflush(stdout);
        pthread_mutex_unlock(philo->left_fork);
		printf("philo %d vratil left fork\n", philo -> id);
		fflush(stdout);
		if (philo -> data -> died == 1)
		{
			printf("philo %d chcipnul   %lld  \n", (philo -> id), time);
			fflush(stdout);
			break;
		}
		printf ("philo %d is sleeping\n", philo -> id);
		fflush(stdout);
		ft_usleep(philo -> time_to_sleep);
		printf ("philo %d is thinking\n", philo -> id);
		fflush(stdout);
	}
	return (0);
}

