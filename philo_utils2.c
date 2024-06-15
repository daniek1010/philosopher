/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:38:55 by danevans          #+#    #+#             */
/*   Updated: 2024/06/16 01:31:18 by danevans         ###   ########.fr       */
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
	long	res;

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
