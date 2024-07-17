/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:48:01 by danevans          #+#    #+#             */
/*   Updated: 2024/07/17 22:59:38 by danevans         ###   ########.fr       */
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
		philo_num_error(temp, 1);
	if ((main->argc_count == 5) || (main->argc_count == 6))
	{
		main->num_philo = ft_atoi(temp[0]);
		main->time_to_die = ft_atoi(temp[1]);
		main->time_to_eat = ft_atoi(temp[2]);
		main->time_to_sleep = ft_atoi(temp[3]);
		if (main->time_to_die < 60 || main->time_to_sleep < 60
			|| main->time_to_die < 60)
			philo_num_error(temp, 3);
		if (main->argc_count == 6)
			main->sum_to_eat = ft_atoi(temp[4]);
		else if (main->argc_count == 5)
			main->sum_to_eat = -1;
	}
	if (main->num_philo > 200 || main->num_philo < 1)
		philo_num_error(temp, 2);
	free_matrix(temp);
	return (1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	index;
	char			*str;

	if (start >= ft_strlen(s) || len <= 0)
	{
		str = (char *)malloc(sizeof(char));
		if (str == NULL)
			return (NULL);
		*str = '\0';
		return (str);
	}
	if ((ft_strlen(s) - start) < len)
		len = ft_strlen(s) - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	index = 0;
	while (index < len && s[start + index] != '\0')
	{
		str[index] = s[start + index];
		index++;
	}
	str[index] = '\0';
	return (str);
}
