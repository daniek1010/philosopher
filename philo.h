/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:39:13 by danevans          #+#    #+#             */
/*   Updated: 2024/04/29 23:16:41 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H

# define PHILO_H

#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <sys/time.h>
#include <pthread.h>

# define TRUE 1
# define FALSE 0

/*fancy color*/
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/*alias mutex define*/
typedef pthread_mutex_t t_mtx;
typedef	struct s_input	t_input;
typedef struct s_main	t_main;
typedef struct s_philo	t_philo;



/*created this for mutext and thread*/
typedef enum s_code
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}t_code;

/* this contains the fork */
typedef	struct s_fork
{
	int	right;
	int	left;
}t_fork;

/*cmmd args are passed here*/
typedef	struct s_input
{
	int 		num_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		sum_to_eat;
	
}t_input;

/* every philo should have*/
typedef struct s_philo
{
	int			id;
	int			index;
	int			meals_ate;
	long		last_time_ate;
	pthread_t	thread;
	t_fork		fork;
	t_input		input;
	t_main		*main;
}t_philo;

typedef struct s_main
{
	bool		all_thread_created;
	bool		is_dead; // not initialised
	bool		full; 
	int			n_thread;
	long		t0;
	t_input		input;
	t_fork		fork;
	t_mtx		*forks;
	t_mtx		write;
	t_philo		*philo;
	pthread_t	checker;
}t_main;







int		ft_parse(int argc, char *argv[], t_main *main);
char	**param_split(int argc, char *argv[], t_main *main);
char	**ft_splitt(char const *s, char c, long *count);
void		philo_eating(t_philo *philo, int index);
void		sleep_time(t_philo *philo);
void	think_time(t_philo *philo);
int		philos_is_dead(t_philo *philo, int *i);
void	*checker_rout(void *data);

/*Declaration of mal_pth.c files*/
void	*mal_create(size_t bytes);
void	mutex_jobs(t_mtx *mutex, t_code opcode);
void	mutex_error(int status, t_code opcode);
void	thread_jobs(pthread_t *thread, void *(*foo)(void *), void *data, t_code opcode);
void	thread_error(int status, t_code opcode);


/*exit with error message*/
void	error_exit(const char *error);

void 	data_init (t_main *table);
int	philo_print(t_philo *philo, int id, char *color, char *status);
void	precise_usleep(long ms);
long	get_current_time(void);
#endif 
