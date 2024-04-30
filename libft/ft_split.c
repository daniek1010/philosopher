/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:03:47 by danevans          #+#    #+#             */
/*   Updated: 2023/07/22 10:48:12 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	control;

	i = 0;
	count = 0;
	control = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && control == 0)
		{
			count++;
			control = 1;
		}
		else if (s[i] == c)
			control = 0;
		i++;
	}
	return (count);
}

static void	*free_str(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free (result[i]);
		i++;
	}
	free (result);
	return (NULL);
}

static char	**write_str(char const *s, char c, char **result, int start)
{
	size_t	i;
	int		j;	

	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			result[j++] = ft_substr(s, start, i - start);
			if (result[j - 1] == NULL)
			{
				free_str (result);
				return (NULL);
			}
			start = -1;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	int		start;
	char	**result;

	size = count_words(s, c);
	if (!s || size == 0)
	{
		result = (char **)malloc(sizeof(char *) * (size + 1));
		if (!result)
			return (NULL);
		*result = NULL;
	}
	else
	{
		result = (char **)malloc(sizeof(char *) * (size + 1));
		if (!result)
			return (NULL);
		start = -1;
		result = write_str(s, c, result, start);
	}
	return (result);
}
