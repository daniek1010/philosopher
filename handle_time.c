/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:40:09 by danevans          #+#    #+#             */
/*   Updated: 2024/06/11 14:41:54 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "philo.h"

/* This would get return in ms */
long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_exit("TIME FAILED");
	else
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

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
	elapsed = 0;
	while (ms > elapsed)
	{
		time_end = get_current_time();
		elapsed = time_end - time_start;
		rem = ms - elapsed;
		if (rem > 100000)
			usleep((rem * 1000));
	}
}

void	free_matrix(char *str[])
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
