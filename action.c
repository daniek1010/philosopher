/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:23:05 by danevans          #+#    #+#             */
/*   Updated: 2024/05/10 02:01:26 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* action to eat 
action to sleep
action think */
pthread_mutex_t state_mutex;
void	lock_setter(t_philo *philo, int i)
{
	if (i == 0)
	{
		mutex_jobs(&state_mutex, LOCK);
		philo->last_time_ate = get_current_time();
		//philo->meals_ate++;
		//if (philo->meals_ate == philo->main->input.sum_to_eat)
			//philo->main->full = true;
		// printf("iniside locker @@@  philo_id and mealate %d %d\n", philo->id, philo->meals_ate);
		mutex_jobs(&state_mutex, UNLOCK);
		
	}

	if (i == 1)
	{
		mutex_jobs(&state_mutex, LOCK);
		// philo->last_time_ate = get_current_time();
		// philo->meals_ate++;
		// if (philo->meals_ate == philo->main->input.sum_to_eat)
		 	philo->full = true;
		//printf("iniside locker @@@  philo_id and mealate %d %d\n", philo->id, philo->meals_ate);
		mutex_jobs(&state_mutex, UNLOCK);
		
	}
}

void	philo_eating(t_philo *philo)
{

	//printf("philo eat is is dead with philo_id %d %d\n", philo->id, philo->main->is_dead);
	mutex_jobs(&philo->main->forks[philo->fork.left], LOCK);
	philo_print(philo, BLUE, "has taken a fork");
	mutex_jobs(&philo->main->forks[philo->fork.right], LOCK);
	philo_print(philo, BLUE, "has taken a fork");
	philo_print(philo, YELLOW, "is eating");
	lock_setter(philo, 0);
	philo->meals_ate++;
	precise_usleep(philo->main->input.time_to_eat);
	if (philo->meals_ate == philo->main->input.sum_to_eat)
		lock_setter(philo, 1);
	mutex_jobs(&philo->main->forks[philo->fork.left], UNLOCK);
	mutex_jobs(&philo->main->forks[philo->fork.right], UNLOCK);
	
}


void	sleep_time(t_philo *philo)
{
	long	sleep;

	sleep = philo->main->input.time_to_sleep;
	philo_print(philo, GREEN, "is sleeping");
	precise_usleep(sleep);
}

void	think_time(t_philo *philo, bool pre_simulation)
{
	int	t_think;
	int	t_eat;
	int	t_sleep;

	if (!pre_simulation)
		philo_print(philo, CYAN, "is thinking");
	if ((philo->main->input.num_philo % 2 == 0))
		return ;
	t_eat = philo->main->input.time_to_eat;
	t_sleep = philo->main->input.time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if ((t_think < 0))
		t_think = 0;
	precise_usleep(t_think * 0.42);
}

bool	philos_is_dead(t_philo *philo)
{
	long	time;
	long	elapsed;
	// bool	result = false;

	time = get_current_time();
	elapsed = time - philo->last_time_ate;
	if (elapsed > philo->main->input.time_to_die)
		return (true);
	// {
	// 	mutex_jobs(&philo->philo_mutex, LOCK);
	// 	philo->main->is_dead = true;
	// 	mutex_jobs(&philo->philo_mutex, UNLOCK);
	// 	result = true;
	// }
	return (false);
}

int		philo_print(t_philo *philo, char *color, char *status)
{
	long	time;
	long	now;
	int		id;

	id = philo->id;	
	time = get_current_time();
	mutex_jobs(&philo->main->write, LOCK);
	now = time - (philo->main->t0);
	printf("%s%-3ld %-3d %-5s%s\n", color, now, id, status, RESET);
	mutex_jobs(&philo->main->write, UNLOCK);
	
}

