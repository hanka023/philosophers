# include "philo.h"
#include <stdio.h>
// int check()
// {

// }
//  void philo_1()
//  {
	 // // 1. Vezme svou jedinou vidličku
        // pthread_mutex_lock(philo->left_fork);
        // printf( "philo has taken a fork");

        // // 2. Čeká, dokud nezemře (čekání nastavené na čas do smrti)
        // usleep(philo->time_to_die);

        // // 3. Odemkne vidličku a ukončí vlákno
        // pthread_mutex_unlock(philo->left_fork);
 //}

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
        return 0 ;
    }
	if ((philo -> id) %2 != 0)
		ft_usleep(2);
	
	if (philo -> id == 1)
		ft_usleep (5);
	(philo -> last_meal) = get_time_in_ms ();
	while (1)
	{
		printf ("while jede \n");
		printf ("philo %d meals eaten [%d] to eat [%d]\n", philo -> id, philo -> meals_eaten , philo -> num_to_eat);
		if ((philo -> meals_eaten) >= (philo -> num_to_eat))
		{
			printf("philo %d is finished\n", philo -> id);
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
			printf("philo %d ma obe vidlicky\n", philo -> id);
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

		printf ("philo %d is eating\n", philo -> id);
		fflush(stdout);
		//printf ("x x x philo %ld last meal ------- puvodni hodnota\n", philo -> last_meal);
		//fflush(stdout);
		
		(philo -> last_meal) = get_time_in_ms();
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
			printf("philo %d chcipnul  ---  moc dlouho cekal na vidlicku %lld  \n", (philo -> id), time);
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

