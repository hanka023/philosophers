# include "philo.h"
#include <stdio.h>

long long count_time_to_think(t_philo *philo)
{
	long long time_to_think;

	time_to_think = (philo->time_to_die - (get_time_in_ms() - philo->last_meal) - philo->time_to_eat) / 2;
		if (time_to_think < 0)
		    time_to_think = 0;
		if (time_to_think > 1000)
		    time_to_think = 200;
	return (time_to_think);
}

void *routine (void *arg)
{
	t_philo *philo;
	long long time;
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

	// if (philo->data->num_of_philos % 2 != 0)
	// 	ft_usleep (2);
	//count_time_to_think(philo);

	time = get_time_in_ms();

	int w = 1;
	while (1)
	{
		if ((philo -> meals_eaten) >= (philo -> num_to_eat))
		{
			printf("philo %d is finished\n", philo -> id);
			pthread_mutex_lock(&philo->mtx);
			(philo->data->finished) ++;
			printf ("finished philos [%d]\n",(philo->data->finished) );
			pthread_mutex_unlock(&philo->mtx);
			break;
		}
		printf ("\n \n * * * %d.kolo * * * \n\n ", w);
		++w;
		
		 if (philo -> data -> died == 1)
		 {
		 	printf ("philo %d chcipnul * * * %lld * * *bez jidla [%lld] \n", philo -> id, time,  get_time_in_ms() -  philo -> last_meal);
		 	break;
		 }
		if (philo -> id %2 == 0)
		{	
			pthread_mutex_lock(philo -> right_fork);
			pthread_mutex_lock(philo -> left_fork);
		}
		else
		{
			pthread_mutex_lock(philo -> left_fork);
			pthread_mutex_lock(philo -> right_fork);
		}
		pthread_mutex_lock(&philo->mtx);
		remaining = philo->time_to_die - (get_time_in_ms() - philo->last_meal);
		printf("* * * philo %d ji, zbývá mu do smrti: %lld ms * * * cas [%lld]\n", philo->id, remaining, get_time_in_ms());
		if (remaining <= 0)
		{
			printf ("philo %d chcipnul * * * %lld * * *bez jidla [%lld] \n", philo -> id, time,  get_time_in_ms() -  philo -> last_meal);
			((philo -> data -> died) = 1);
		}
		(philo -> last_meal) = get_time_in_ms();
		remaining = philo->time_to_die - (get_time_in_ms() - philo->last_meal);
		(philo -> meals_eaten) ++;
		if (philo -> meals_eaten == philo -> num_to_eat)
			philo -> finish = 1;
		printf("* * * p %d se najedl, zbývá mu do smrti: %lld ms *   cas [%lld]\n", philo->id, remaining, get_time_in_ms());
		pthread_mutex_unlock(&philo->mtx);
		
		ft_usleep(philo -> time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
		if (philo -> data -> died == 1)
			break;
		ft_usleep(philo -> time_to_sleep);
		remaining = philo->time_to_die - (get_time_in_ms() - philo->last_meal);
		//time_to_think = count_time_to_think(philo);
		time_to_think = remaining / 2;
		printf("philo id [%d]	remaining:[%lld]   time to think [%lld] \n",philo -> id, remaining, time_to_think);
		if (remaining > 200 )
			ft_usleep (25);
		else if (remaining > 10)
			ft_usleep(time_to_think);
	}
	return (0);
}
