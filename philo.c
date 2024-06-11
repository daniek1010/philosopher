/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:29:18 by danevans          #+#    #+#             */
/*   Updated: 2024/06/11 14:18:11 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[]) 
{
	if (argc == 1)
		error_exit("Args should be 4 max 5 "
			"num1 num2 num3 num4 num5[optional]");
	t_main	main;
	ft_parse(argc, argv, &main);
	data_init(&main);
	if (main.num_philo == 1)
	{
		thread_jobs(&main.philo[0].thread, &lone_diner, &main.philo[0], CREATE);
		thread_jobs(&main.checker, &checker_rout, &main, CREATE);
		thread_jobs(&main.philo[0].thread, &routine, &main.philo[0], JOIN);
		thread_jobs(&main.checker, &checker_rout, &main, JOIN);
	}
	else if (main.num_philo > 1)
		mutiple_diner(&main);
	ft_cleanup(&main);
		
}

void	*lone_diner(void *data)
{
	t_philo		*philo;

	philo = (t_philo *) data;
	philo_print(philo, BLUE, "has taken a fork", "EATING");
	set_long(&philo->philo_mutex, &philo->last_time_ate, get_current_time());
	while(!get_bool(&philo->philo_mutex, &philo->main->is_dead))
		precise_usleep(200);
	return (NULL);
}

void	mutiple_diner(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->num_philo)
		thread_jobs(&main->philo[i].thread, &routine, &main->philo[i], CREATE);
	thread_jobs(&main->checker, &checker_rout, main, CREATE);
	i = -1;
	while (++i < main->num_philo)
		thread_jobs(&main->philo[i].thread, &routine, &main->philo[i], JOIN);
	thread_jobs(&main->checker, &checker_rout, main, JOIN);
}
