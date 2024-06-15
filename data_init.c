/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:42:57 by danevans          #+#    #+#             */
/*   Updated: 2024/06/16 01:14:13 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Every philo is assigned a left and right fuck*/
static void	fill_philo(t_main *main, int i, int j)
{
	main->philo[i].full = false;
	main->philo[i].id = i + 1;
	main->philo[i].meals_ate = 0;
	main->philo[i].last_time_ate = main->t0;
	main->philo[i].fork.left = i;
	main->philo[i].fork.right = j;
	mutex_jobs(&main->philo[i].philo_mutex, INIT);
	main->philo[i].main = main;
}

/*	Assigning left and right fork with my i , j */
static void	assign_fork(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < main->num_philo)
	{
		fill_philo(main, i, j);
		i++;
		j++;
	}
	j = 0;
	fill_philo(main, i, j);
}

/* Initializing my main data, nothing fancy here */
void	data_init(t_main *main)
{
	int	i;

	main->t0 = get_current_time();
	main->is_dead = false;
	mutex_jobs(&main->lock_mtx, INIT);
	mutex_jobs(&main->write, INIT);
	main->forks = mal_create(main->num_philo * sizeof(t_mtx));
	main->philo = mal_create(main->num_philo * sizeof(t_philo));
	assign_fork(main);
	i = -1;
	while (++i < main->num_philo)
		mutex_jobs(&main->forks[i], INIT);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	de_synchronize_philos(philo);
	while (!get_bool(&philo->philo_mutex, &philo->main->is_dead))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		philo_eating(philo);
		sleep_time(philo);
		think_time(philo, false);
	}
	return (NULL);
}

void	*checker_rout(void *data)
{
	t_main	*main;
	int		i;

	main = (t_main *)data;
	while (!get_bool(&main->lock_mtx, &main->is_dead))
	{
		i = 0;
		while (i < main->num_philo && (!get_bool(&main->lock_mtx,
					&main->is_dead)))
		{
			if (philos_is_dead(&main->philo[i]))
			{
				set_bool(&main->lock_mtx, &main->is_dead, true);
				philo_print(&main->philo[i], RED, "dead", "DEAD");
			}
			i++;
		}
		usleep(10000);
	}
	return (NULL);
}
