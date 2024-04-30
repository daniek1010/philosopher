/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:48:01 by danevans          #+#    #+#             */
/*   Updated: 2024/04/10 13:46:09 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "philo.h"
//this should a call a function that passes the argc and argv
	//check for validity and return;
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
	holder = ft_calloc(1, 1); // have to handle the calloc funtion here 
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
	container = ft_splitt(holder, ' ', &main->input.sum_to_eat);
	free(holder);
	return (container);
}

/*this should be passing the splitted str into the struct */
int	ft_parse(int argc, char *argv[], t_main *main)
{
	char	**temp;

	temp = param_split(argc, argv, main);
	if ((main->input.sum_to_eat != 5) && (main->input.sum_to_eat != 6))
		error_exit("Args should be 4 max 5 "
			"num1 num2 num3 num4 num5[optional]");
	if ((main->input.sum_to_eat == 5) || (main->input.sum_to_eat == 6))
	{
		main->input.num_philo = ft_atoi(argv[1]);
		main->input.time_to_die = ft_atoi(argv[2]);
		main->input.time_to_eat = ft_atoi(argv[3]);
		main->input.time_to_sleep = ft_atoi(argv[4]);
		// if (main->input.time_to_die < 6e4 || main->input.time_to_sleep < 6e4 
		// 	|| main->input.time_to_die < 6e4)
		// 	error_exit("give value greater than 60ms");
		if (main->input.sum_to_eat == 6)
			main->input.sum_to_eat = ft_atoi(argv[5]);
		else if (main->input.sum_to_eat == 5)
			main->input.sum_to_eat = -1;
		return (0);
	}
}

