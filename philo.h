/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:39:13 by danevans          #+#    #+#             */
/*   Updated: 2024/07/17 22:34:31 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stddef.h>
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0

/*fancy color*/
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

/*alias mutex define*/
typedef pthread_mutex_t	t_mtx;
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
}	t_code;

/* this contains the fork */
typedef struct s_fork
{
	int	right;
	int	left;
}	t_fork;

/* every philo should have*/
typedef struct s_philo
{
	int			id;
	int			index;
	int			meals_ate;
	bool		full;
	long		last_time_ate;
	t_fork		fork;
	pthread_t	thread;
	t_main		*main;
	t_mtx		philo_mutex;
	t_mtx		lock;
}	t_philo;

typedef struct s_main
{
	t_mtx		*forks;
	t_mtx		write;
	t_philo		*philo;
	long		argc_count;
	int			num_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		sum_to_eat;
	bool		all_thread_created;
	bool		is_dead;
	int			n_thread;
	long		t0;
	t_mtx		lock_mtx;
	pthread_t	checker;
}	t_main;

void	mutiple_diner(t_main *main);
void	*lone_diner(void *data);
void	free_matrix(char *str[]);

void	ft_cleanup(t_main *main);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx	*mutex, bool *dest, bool value);
void	set_long(t_mtx	*mutex, long *dest, long value);
void	de_synchronize_philos(t_philo *philo);
long	get_long(t_mtx	*mutex, long *value);

int		get_meals_ate(t_mtx *mutex, int *variable);
void	set_meals_ate(t_mtx *mutex, int *variable);

int		ft_parse(int argc, char *argv[], t_main *main);
char	**param_split(int argc, char *argv[], t_main *main);
char	**ft_splitt(char const *s, char c, long *count);
void	philo_eating(t_philo *philo);
void	sleep_time(t_philo *philo);
void	think_time(t_philo *philo, bool pre_simulation);
bool	philos_is_dead(t_philo *philo);
void	*checker_rout(void *data);
void	data_init(t_main *main);
void	*routine(void *data);

/*Declaration of mal_pth.c files*/
void	*mal_create(size_t bytes);
void	mutex_jobs(t_mtx *mutex, t_code opcode);
void	mutex_error(int status, t_code opcode);
void	thread_jobs(pthread_t *thread, void *(*foo)(void *),
			void *data, t_code opcode);
void	thread_error(int status, t_code opcode);

/*exit with error message*/
void	error_exit(const char *error);

void	data_init(t_main *table);
int		philo_print(t_philo *philo, char *color, char *status, char *str);
void	precise_usleep(long ms);
long	get_current_time(void);

int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);

void	philo_num_error(char *str[], int num);
#endif 
