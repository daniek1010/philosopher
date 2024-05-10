/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:42:57 by danevans          #+#    #+#             */
/*   Updated: 2024/05/10 02:42:51 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fill_philo(t_main *main, int i, int j);
void data_init (t_main *main);
void	*routine(void *data);

static void	assign_fork(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < main->input.num_philo)
	{
		fill_philo(main, i , j);
		i++;
		j++;
	}
	j = 0;
	fill_philo(main, i, j);
}

/*Every philo is assigned a left and right fuck*/
static void	fill_philo(t_main *main, int i, int j)
{
	main->philo[i].index = i;
	main->philo[i].id = i + 1;
	main->philo[i].meals_ate = 0;
	main->philo[i].last_time_ate = main->t0;
	main->philo[i].fork.left = i;
	main->philo[i].fork.right = j;
	mutex_jobs(&main->philo->philo_mutex, INIT);
	
	main->philo[i].main = main;
}

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->main->input.num_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(30000);
	}
	else
	{
		if (philo->id % 2)
			think_time(philo, true);
	}
}

void data_init (t_main *main)
{
	int	i;

	i = -1;
	main->t0 = get_current_time();
	main->full = false;
	main->is_dead = false;
	main->forks = mal_create(main->input.num_philo * sizeof(t_mtx));
	while (++i < main->input.num_philo)
		mutex_jobs(&main->forks[i], INIT);
	mutex_jobs(&main->write, INIT);
	main->philo = mal_create(main->input.num_philo * sizeof(t_philo));
	assign_fork(main);
	i = -1;
	while (++i < main->input.num_philo)
		thread_jobs(&main->philo[i].thread, &routine, &main->philo[i] , CREATE);
	thread_jobs(&main->checker, &checker_rout, main, CREATE);
	i = -1;
	while (++i < main->input.num_philo)
		thread_jobs(&main->philo[i].thread, &routine, &main->philo[i] , JOIN);
	thread_jobs(&main->checker, &checker_rout, main, JOIN);
}

// void	routine_execute(t_philo *philo)
// {
//     philo_eating(philo);
// 	if (philo->full || philo->main->is_dead)
// 		return ;
//     sleep_time(philo);
//     think_time(philo, false);	
// }

// void	*routine(void *data)
// {
// 	t_philo	*philo;
// 	int		i;

// 	philo = (t_philo *)data;
// 	de_synchronize_philos(philo);
// 	while (!philo->main->is_dead)
// 	{
// 		printf("what is is dead with philo_id %d %d\n", philo->id, philo->main->is_dead);
// 		fflush(stdout);
// 		if (philo->full)
// 			break ;
// 		philo_eating(philo);
// 		sleep_time(philo);
// 		think_time(philo, false);	
// 	}
// 	return (NULL);
// }

void *routine(void *data) {
    t_philo *philo = (t_philo *)data;
    de_synchronize_philos(philo);

    while (!philo->main->is_dead) {
		printf("what is is dead with philo_id %d %d\n", philo->id, philo->main->is_dead);
        pthread_mutex_lock(&philo->philo_mutex);
        if (philo->main->is_dead) {
            pthread_mutex_unlock(&philo->philo_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->philo_mutex);

        philo_eating(philo);
        sleep_time(philo);
        think_time(philo, false);
    }
    return NULL;
}


void	*checker_rout(void *data)
{
	t_main	*main;
	int		i;

	main = (t_main *)data;
	
	while (!main->is_dead && !main->philo->full)
	{
		i = 0;
		while (i < main->input.num_philo && !main->is_dead)
		{
			if (philos_is_dead(main->philo + i))
			{
				mutex_jobs(&main->lock, LOCK);
				main->is_dead = true;
				mutex_jobs(&main->lock, UNLOCK);
				philo_print(&main->philo[i], RED, "dead");
			}
			i++;
		}
		//usleep(10000);
	}
	return (NULL);
}


// void	*routine(void *data)
// {
// 	t_philo	*philo;
// 	int		i;

// 	philo = (t_philo *)data;
// 	de_synchronize_philos(philo);
// 	// if (philo->main->input.sum_to_eat > 0)
// 		while (philo->full == false && philo->main->is_dead == false)
// 		{
// 			if (philo->main->is_dead == true)
// 				break ;
// 			philo_eating(philo);
// 			if (philo->full || philo->main->is_dead)
// 				break ;
// 			sleep_time(philo);
// 			if (philo->main->is_dead == true)
// 				break ;
// 			think_time(philo, false);	
// 		}
// 			//routine_execute(philo);
// 	// else
// 	// 	while (philo->main->is_dead == false)
// 	// 		routine_execute(philo);		
// 	return (NULL);
// }
