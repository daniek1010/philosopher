/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mal_pth.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:51:31 by danevans          #+#    #+#             */
/*   Updated: 2024/07/21 20:44:09 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*this create return malloced*/
void	*mal_create(size_t bytes)
{
	void	*str;

	str = malloc(bytes);
	if (str == NULL)
		error_exit("malloc fucked you up");
	return (str);
}

/* error checking for mutex init, lock, unlock and destroy*/
void	mutex_error(int status, t_code opcode)
{
	if (status == 0)
		return ;
	else if (EINVAL == status && INIT == opcode)
		error_exit("Invalid mutex attributes.");
	else if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_exit("Invalid mutex");
	else if (EDEADLK == status)
		error_exit("Attempt to relock a mutex that's"
			"already locked by the same thread.");
	else if (EAGAIN == status)
		error_exit("The mutex could not be acquired because the maximum"
			"number of recursive locks for mutex has been exceeded.");
	else if (EINTR == status)
		error_exit("EINTR: The call was interrupted by a signal"
			"before the mutex could be locked.");
	else if (ENOTRECOVERABLE == status)
		error_exit("A deadlock was detected or the mutex"
			"or a process is no longer usable.");
	else if (EBUSY == status && DESTROY == opcode)
		error_exit("The mutex is locked??.");
}

/*error checking for pthread create join and destroy*/
void	thread_error(int status, t_code opcode)
{
	if (status == 0)
		return ;
	else if (EINVAL == status && CREATE == opcode)
		error_exit("Invalid settings in the attributes object.");
	else if (EAGAIN == status)
		error_exit("The system lacks the necessary resources"
			"to create another thread.");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by thread is not joinable.");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread.");
}

/*mutex init lock unlock and destroy*/
void	mutex_jobs(t_mtx *mutex, t_code opcode)
{
	if (INIT == opcode)
		mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (LOCK == opcode)
		mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (DESTROY == opcode)
		mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("opcode for mutex_jobs not found");
}

/*thread create, join detach*/
void	thread_jobs(pthread_t *thread, void *(*foo)(void *),
	void *data, t_code opcode)
{
	if (CREATE == opcode)
		thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("opcode for thread_jobs not found");
}
