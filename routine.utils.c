# include "philo.h"
#include <stdio.h>


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


 // void	print_action(t_philo *philo, char *action)
// {
// 	if (is_simulation_over(philo->program))
// 		return ;
// 	pthread_mutex_lock(&philo->program->write_lock);
// 	if (!is_simulation_over(philo->program))
// 		printf("%zu %d %s\n", get_current_time()
// 			- philo->program->start_time, philo->id, action);
// 	pthread_mutex_unlock(&philo->program->write_lock);
// }
