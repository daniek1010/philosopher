/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:23:05 by danevans          #+#    #+#             */
/*   Updated: 2024/06/11 15:56:13 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* action to eat 
action to sleep
action think */
void	philo_eating(t_philo *philo)
{
	mutex_jobs(&philo->main->forks[philo->fork.right], LOCK);
	philo_print(philo, BLUE, "has taken a fork", "EATING");
	mutex_jobs(&philo->main->forks[philo->fork.left], LOCK);
	philo_print(philo, BLUE, "has taken a fork", "EATING");
	philo_print(philo, YELLOW, "is eating", "EATING");
	set_long(&philo->philo_mutex, &philo->last_time_ate, get_current_time());
	philo->meals_ate++;
	precise_usleep(philo->main->time_to_eat);
	if (philo->meals_ate == philo->main->sum_to_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_jobs(&philo->main->forks[philo->fork.right], UNLOCK);
	mutex_jobs(&philo->main->forks[philo->fork.left], UNLOCK);
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
	elapsed = time - philo->last_time_ate;
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
	if (!get_bool(&philo->philo_mutex, &philo->main->is_dead))
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
}
