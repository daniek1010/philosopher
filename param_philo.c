/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:48:01 by danevans          #+#    #+#             */
/*   Updated: 2024/05/11 05:36:13 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*if the whole string are num 0 - 9*/
static int	digit_check(int argc, char *argv[])
{
	int		i;
	int		j;
	char	*holder;

	if (argc == 1)
		return (FALSE);
	i = 1;
	while (i < argc)
	{
		holder = argv[i];
		if (holder == NULL)
			return (FALSE);
		j = 0;
		while (holder[j] != '\0')
		{
			if (((holder[j] < '0') || (holder[j] > '9' )) && (holder[j] != ' '))
				error_exit("Args contains non digit!!"
					"Enter digit only 0 - 9 !!!");
			j++;
		}
		i++;
	}
	return (TRUE);
}

/* this split argv into pieces */
char	**param_split(int argc, char *argv[], t_main *main)
{
	int		i;
	int		size;
	char	*holder;
	char	*temp;
	char	**container;

	if (!digit_check(argc, argv))
		return (NULL);
	holder = ft_calloc(1, 1);
	i = 0;
	while (++i < argc)
	{
		temp = ft_strjoin(holder, argv[i]);
		free (holder);
		holder = temp;
		if (temp != NULL)
		{
			temp = ft_strjoin(holder, " ");
			free(holder);
			holder = temp;
		}
	}
	container = ft_splitt(holder, ' ', &main->argc_count);
	free(holder);
	return (container);
}

/*this should be passing the splitted str into the struct */
int	ft_parse(int argc, char *argv[], t_main *main)
{
	char	**temp;

	temp = param_split(argc, argv, main);
	if ((main->argc_count != 5) && (main->argc_count != 6))
	{
		free_matrix(temp);
		error_exit("Args should be 4 max 5 "
			"num1 num2 num3 num4 num5[optional]");
	}
	if ((main->argc_count == 5) || (main->argc_count == 6))
	{
		main->num_philo = ft_atoi(temp[0]);
		main->time_to_die = ft_atoi(temp[1]);
		main->time_to_eat = ft_atoi(temp[2]);
		main->time_to_sleep = ft_atoi(temp[3]);
		if (main->time_to_die < 60 || main->time_to_sleep < 60
			|| main->time_to_die < 60)
			error_exit("give value greater than 60ms");
		if (main->argc_count == 6)
			main->sum_to_eat = ft_atoi(temp[4]);
		else if (main->argc_count == 5)
			main->sum_to_eat = -1;
	}
	if (main->num_philo > 200)
	{
		free_matrix(temp);
		error_exit("Philo should be less than 200");
	}
	free_matrix(temp);
	return (1);
}
