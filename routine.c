# include "philo.h"
#include <stdio.h>



long long count_time_to_think(t_philo *philo)
{
	long long time_to_think;


	time_to_think = (philo->time_to_die - (get_time_in_ms() - philo->last_meal) - philo->time_to_eat) / 2;
		if (time_to_think < 0)
		    time_to_think = 0;
		if (time_to_think > 1000)
		    time_to_think = 200; // Maximální rozumná pauza

	return (time_to_think);
}



void *routine (void *arg)
{
	t_philo *philo;
	size_t time;
	long long time_to_think;
	long long remaining;

	philo = (t_philo *)arg;

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
		ft_usleep(1);
	
	if (philo -> id == 1)
		ft_usleep (2);
	pthread_mutex_lock(&philo->mtx);
	(philo -> last_meal) = get_time_in_ms ();
	pthread_mutex_unlock(&philo->mtx);

	if (philo->data->num_of_philos % 2 != 0)
		//ft_usleep (2);
		count_time_to_think(philo);

	time = get_time_in_ms();

	int w = 1;
	while (1)
	{
	
		printf ("\n \n * * * %d.kolo * * * \n\n ", w);
		++w;

		printf("* * * time: %lld \n", get_time_in_ms()- time);
		remaining = philo->time_to_die - (get_time_in_ms() - philo->last_meal);
		printf("* * *  philo %d ji, zbývá mu do smrti: %lld ms * * * \n", philo->id, remaining);

		printf ("philo %d meals eaten [%d] to eat [%d]\n", philo -> id, philo -> meals_eaten , philo -> num_to_eat);
		if ((philo -> meals_eaten) >= (philo -> num_to_eat))
		{
			printf("philo %d is finished\n", philo -> id);
			break;
		}
		if (philo -> data -> died == 1)
		{
			printf ("philo %d chcipnul * * * %ld * * *bez jidla [%lld] \n", philo -> id, time,  get_time_in_ms() -  philo -> last_meal);
			break;
		}
	
		if (philo -> id %2 == 0)
		{	
			pthread_mutex_lock(philo -> right_fork);
			printf("philo %d [id 2 == 0] has taken right fork\n", philo -> id);
			pthread_mutex_lock(philo -> left_fork);
			printf("philo %d [id 2 == 0] has taken left fork\n", philo -> id);
			//printf("philo %d [id %2 == 0] ma obe vidlicky\n", philo -> id);
		}
		else
		{
			pthread_mutex_lock(philo -> left_fork);
			printf("philo %d [id 1] has taken left fork\n", philo -> id);
			pthread_mutex_lock(philo -> right_fork);
			printf("philo %d [id 1] has taken right fork\n", philo -> id);
		}
		
		printf ("philo %d is eating\n", philo -> id);


		printf ("x x x philo %ld last meal ------- puvodni hodnota\n", philo -> last_meal);
		printf(" ------------- [1]  philo %d jde jist, zbývá mu do smrti: %lld ms * * * \n", philo->id, remaining);
		
		pthread_mutex_lock(&philo->mtx);
		(philo -> last_meal) = get_time_in_ms();
		remaining = philo->time_to_die - (get_time_in_ms() - philo->last_meal);
		pthread_mutex_unlock(&philo->mtx);
		
		
		printf("------------- [2] philo %d dojedl, zbývá mu do smrti: %lld ms * * * \n", philo->id, remaining);
		printf ("x x x philo %ld last meal --------nova hodnota\n", philo -> last_meal);
	
		(philo -> meals_eaten) ++;
		printf ("philo %d meals eaten: %d\n", philo -> id, philo -> meals_eaten);
		printf(" + + + + kontrola  - bez jidla [%lld] + + + +time [%lld]\n", (get_time_in_ms() - (philo -> last_meal)),get_time_in_ms());
		ft_usleep(philo -> time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		printf("philo %d vratil right fork\n", philo -> id);

        pthread_mutex_unlock(philo->left_fork);
		printf("philo %d vratil left fork\n", philo -> id);
		
		if (philo -> data -> died == 1)
		{
			printf("philo %d chcipnul  ---  moc dlouho cekal na vidlicku %lld  \n", (philo -> id), get_time_in_ms() - (philo -> last_meal) );
		
			break;
		}
		
		ft_usleep(philo -> time_to_sleep);
		printf ("philo %d is sleeping\n", philo -> id);
		printf("philo %d spi  cas [%lld] bez jidla [%lld] \n", (philo -> id), get_time_in_ms(), get_time_in_ms() - (philo -> last_meal) );

		remaining = philo->time_to_die - (get_time_in_ms() - philo->last_meal);
		printf("------------- [2] philo %d dospal, zbývá mu do smrti: %lld ms * * * \n", philo->id, remaining);

		time_to_think = count_time_to_think(philo);
		ft_usleep(time_to_think);
		printf ("philo %d is thinking [%lldms]\n", philo -> id, time_to_think );
		printf ("philo %d time to die [%lldms]\n", philo -> id,(philo -> time_to_die - (get_time_in_ms() - philo->last_meal)));

	}
	return (0);
}

