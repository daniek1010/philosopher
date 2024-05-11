/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:38:55 by danevans          #+#    #+#             */
/*   Updated: 2024/05/11 05:33:37 by danevans         ###   ########.fr       */
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