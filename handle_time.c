/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:40:09 by danevans          #+#    #+#             */
/*   Updated: 2024/04/29 13:21:55 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_exit("TIME FAILED");
	else
		return(time.tv_sec * 1000) + (time.tv_usec / 1000);
}

// long	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		error_exit("TIME FAILED");
// 	else
// 	{
// 		get_time - 
// 	}
// 		return(time.tv_sec * 1000) + (time.tv_usec / 1000);
// }


/* this uses usleep to sleep the rem,
checks time used - time to sleep, used 1e4 
to balance syscall (usleep) and busywait */
void	precise_usleep(long ms)
{
	double	elapsed;
	double	rem;
	long	time_start;
	long	time_end;

	time_start = get_current_time();
	//printf("========== %ld", time_start);
	elapsed = 0;
	while (ms > elapsed)
		{
			time_end = get_current_time();
			elapsed = time_end - time_start;
			rem = ms - elapsed;
			//printf("========== %f\n", rem);
			if (rem > 100000)
				usleep((rem * 1000));
		}
	
	//printf("got \n");
}

int main(int argc, char *argv[]) 
{
	int i = 0;
	t_main	main;
	ft_parse(argc, argv, &main);
	data_init(&main);
	// while (i < main.input.num_philo)
	// {
	// 	printf("value of id = %d, forks %d %d\n", main.philo[i].id, main.philo[i].fork.left, main.philo[i].fork.right);
	// 	//input.philo[i].times_ate++;
	// 	i++;
	// }
	// //printf("here \n");
	// //i = -1;
	// // while (++i < input.num_philo)
	// // 	thread_jobs(&input.philo[i].thread, &routine, &input , JOIN);
	// //mutex_jobs(&input.forks[input.philo->fork.left], DESTROY);
	// i = -1;
	// while (++i < main.input.num_philo)
	// {
	// 	printf("checkingsss  %d %d\n", i, main.philo[i].times_ate);
	// }

	//printf("value of %id, forks %d %d", input.philo->id, input.philo[i].fork.left, input.philo[i].fork.right);
}

