/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:38:55 by danevans          #+#    #+#             */
/*   Updated: 2024/06/11 20:12:57 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	mutex_jobs(mutex, LOCK);
	ret = *value;
	mutex_jobs(mutex, UNLOCK);
	return (ret);
}

void	set_bool(t_mtx	*mutex, bool *dest, bool value)
{
	mutex_jobs(mutex, LOCK);
	*dest = value;
	mutex_jobs(mutex, UNLOCK);
}

void	set_long(t_mtx	*mutex, long *dest, long value)
{
	mutex_jobs(mutex, LOCK);
	*dest = value;
	mutex_jobs(mutex, UNLOCK);
}

long	get_long(t_mtx	*mutex, long *value)
{
	long res;

	mutex_jobs(mutex, LOCK);
	res = *value;
	mutex_jobs(mutex, UNLOCK);
	return (res);
}

void	set_meals_ate(t_mtx *mutex, int *variable)
{
	mutex_jobs(mutex, LOCK);
    (*variable)++;
    mutex_jobs(mutex, UNLOCK);
}

int	get_meals_ate(t_mtx *mutex, int *variable)
{
	int	ate;

	mutex_jobs(mutex, LOCK);
    ate = *variable;
    mutex_jobs(mutex, UNLOCK);
	return (ate);
}

/*	I used this function to slow down the immediate 
	the grabing or racing for the fork by focusing
	on the odd philo_id and then allowing then to think*/
void	de_synchronize_philos(t_philo *philo)
{
	if (philo->main->num_philo % 2 == 0)
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

void	ft_cleanup(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->num_philo)
		mutex_jobs(&main->forks[i], DESTROY);
	i = -1;
	while (++i < main->num_philo)
		mutex_jobs(&main->philo->philo_mutex, DESTROY);
	mutex_jobs(&main->lock_mtx, DESTROY);
	mutex_jobs(&main->write, DESTROY);
	free(main->philo);
	free(main->forks);
	
}