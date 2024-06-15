/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 01:23:56 by danevans          #+#    #+#             */
/*   Updated: 2024/06/16 01:40:49 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	result = malloc(nmemb * size);
	if (result == NULL)
		return (NULL);
	ft_memset(result, '\0', nmemb * size);
	return (result);
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

void	philo_num_error(char *str[], int num)
{
	if (num == 1)
	{
		free_matrix(str);
		error_exit("Args should be 4 max 5 "
			"num1 num2 num3 num4 num5[optional]");
	}
	else if (num == 2)
	{
		free_matrix(str);
		error_exit("Philo > 1 && Philo < 200");
	}
}
