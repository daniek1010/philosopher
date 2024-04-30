/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:23:05 by danevans          #+#    #+#             */
/*   Updated: 2024/04/29 23:55:50 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* action to eat 
action to sleep
action think */

// void	de_synchronize_philos(t_main *main, int i)
// {
// 	if (main->input.num_philo % 2 == 0)
// 	{
// 		if (main->philo[i].id % 2 == 0)
// 			precise_usleep(3e4);
// 	}
// 	else
// 	{
// 		if (main->philo[i].id % 2)
// 			think_time(main, i);
// 	}
// }
	
void	philo_eating(t_philo *philo, int index)
{
	// printf("value ================== %d %d\n", i, philo->id);
	mutex_jobs(&philo->main->forks[philo->main->philo[index].fork.left], LOCK);
	philo_print(philo, philo->id, BLUE, "has taken a fork");
	mutex_jobs(&philo->main->forks[philo->main->philo[index].fork.right], LOCK);
	philo_print(philo, philo->id, BLUE, "has taken a fork");
	philo_print(philo, philo->id, YELLOW, "is eating");
	philo->last_time_ate = get_current_time();
	philo->meals_ate++;
	// printf("this is meal count and id %ld %d  %d\n", philo->last_time_ate, philo->id, philo->meals_ate);
	if (philo->meals_ate == philo->main->input.sum_to_eat)
	{
		printf("here\n");
		philo->main->full = true;
	}
	precise_usleep(philo->main->input.time_to_eat);
	mutex_jobs(&philo->main->forks[philo->main->philo[index].fork.left], UNLOCK);
	mutex_jobs(&philo->main->forks[philo->main->philo[index].fork.right], UNLOCK);
	// printf("value =====###### %d %d\n", i, philo->id);
}


void	sleep_time(t_philo *philo)
{
	long	sleep;

	sleep = philo->main->input.time_to_sleep;
	// printf("value of sleep %ld %d\n", sleep, philo->id);
	philo_print(philo, philo->id, GREEN, "is sleeping");
	precise_usleep(sleep);
}

void	think_time(t_philo *philo)
{
	int	t_think;
	int	t_eat;
	int	t_sleep;
	int	id;

	id = philo->id;
	if (!(philo->main->input.num_philo % 2 == 0))
	{
		t_eat = philo->main->input.time_to_eat;
		t_sleep = philo->main->input.time_to_sleep;
		t_think = (t_eat * 2) - t_sleep;
		if (!(t_think < 0))
			precise_usleep(t_think * 0.42);
		philo_print(philo, id, GREEN, "is thinking");
	}
}

int		philos_is_dead(t_philo *philo, int *i)
{
	long	time;
	long	elapsed;

	if (*i == philo->main->input.num_philo)
		*i = 0;
	time = get_current_time();
	elapsed = time - philo->last_time_ate;
	printf("time is %ld %ld %ld %ld  %d\n", elapsed, time , philo->last_time_ate, philo->main->input.time_to_die, *i);
	if (elapsed > philo->main->input.time_to_die)
	{
		philo_print(philo, philo->main->philo[*i].id, BLUE, "DEAD");
		philo->main->is_dead = true;
		return (TRUE);
	}
	return (FALSE);
}

int		philo_print(t_philo *philo, int id, char *color, char *status)
{
	long	time;
	long	now;
	
	time = get_current_time();
	now = time - (philo->main->t0);
	mutex_jobs(&philo->main->write, LOCK);
	if (philo->main->is_dead == true)
	{
		mutex_jobs(&philo->main->write, UNLOCK);
		return (FALSE);
	}	
	else
		printf("%s%-3ld %-3d %-5s%s\n", color, now, id, status, RESET);
	mutex_jobs(&philo->main->write, UNLOCK);
}

