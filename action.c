/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:23:05 by danevans          #+#    #+#             */
/*   Updated: 2024/07/21 20:40:49 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* action to eat 
action to sleep
action think */
void	philo_eating(t_philo *philo)
{
	if (philo->fork.left < philo->fork.right)
	{
		philo->first_fork = &philo->main->forks[philo->fork.left];
		philo->second_fork = &philo->main->forks[philo->fork.right];
	}
	else
	{
		philo->first_fork = &philo->main->forks[philo->fork.right];
		philo->second_fork = &philo->main->forks[philo->fork.left];
	}
	mutex_jobs(philo->first_fork, LOCK);
	philo_print(philo, BLUE, "has taken a fork", "EATING");
	mutex_jobs(philo->second_fork, LOCK);
	philo_print(philo, BLUE, "has taken a fork", "EATING");
	philo_print(philo, YELLOW, "is eating", "EATING");
	set_long(&philo->philo_mutex, &philo->last_time_ate, get_current_time());
	set_meals_ate(&philo->philo_mutex, &philo->meals_ate);
	precise_usleep(philo->main->time_to_eat);
	if (get_meals_ate(&philo->philo_mutex, &philo->meals_ate)
		== philo->main->sum_to_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_jobs(philo->first_fork, UNLOCK);
	mutex_jobs(philo->second_fork, UNLOCK);
}

void	sleep_time(t_philo *philo)
{
	long	sleep;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	sleep = philo->main->time_to_sleep;
	philo_print(philo, GREEN, "is sleeping", "SLEEPING");
	precise_usleep(sleep);
}

void	think_time(t_philo *philo, bool pre_simulation)
{
	int	t_think;
	int	t_eat;
	int	t_sleep;

	if (!pre_simulation)
		philo_print(philo, CYAN, "is thinking", "THINKING");
	if ((philo->main->num_philo % 2 == 0))
		return ;
	t_eat = philo->main->time_to_eat;
	t_sleep = philo->main->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if ((t_think < 0))
		t_think = 0;
	precise_usleep(t_think * 0.42);
}

bool	philos_is_dead(t_philo *philo)
{
	long	time;
	long	elapsed;

	time = get_current_time();
	elapsed = time - get_long(&philo->philo_mutex, &philo->last_time_ate);
	if (elapsed > philo->main->time_to_die)
		return (true);
	return (false);
}

int	philo_print(t_philo *philo, char *color, char *status, char *str)
{
	long	time;
	long	now;
	int		id;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (1);
	id = philo->id;
	time = get_current_time();
	now = time - (philo->main->t0);
	mutex_jobs(&philo->main->write, LOCK);
	if (!get_bool(&philo->main->lock_mtx, &philo->main->is_dead))
	{
		if (ft_strncmp(str, "EATING", ft_strlen(str)) == 0)
			printf("%s%-3ld %-3d %-5s%s\n", color, now, id, status, RESET);
		else if (ft_strncmp(str, "SLEEPING", ft_strlen(str)) == 0)
			printf("%s%-3ld %-3d %-5s%s\n", color, now, id, status, RESET);
		else if (ft_strncmp(str, "THINKING", ft_strlen(str)) == 0)
			printf("%s%-3ld %-3d %-5s%s\n", color, now, id, status, RESET);
	}
	else if (ft_strncmp(str, "DEAD", ft_strlen(str)) == 0)
		printf("%s%-3ld %-3d %-5s%s\n", color, now, id, status, RESET);
	mutex_jobs(&philo->main->write, UNLOCK);
	return (0);
}
