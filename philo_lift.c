/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lift.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:44:22 by danevans          #+#    #+#             */
/*   Updated: 2024/06/16 01:24:42 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	unsigned int	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	index;

	index = 0;
	if (n == 0)
		return (0);
	while (((s1[index] != '\0') || (s2[index] != '\0')) && index < n)
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char) s2[index]);
		index++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	size_t		s1_len;
	size_t		s2_len;
	size_t		i;
	size_t		j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
		index++;
	return (index);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*cast;
	size_t			i;

	cast = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		cast[i] = c;
		i++;
	}
	return (s);
}
