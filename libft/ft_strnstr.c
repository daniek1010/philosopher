/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:23:16 by danevans          #+#    #+#             */
/*   Updated: 2023/07/20 11:51:04 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	len;

	len = ft_strlen(little);
	if (len == 0)
		return ((char *)big);
	while (*big != '\0' && n >= len)
	{
		if (ft_strncmp (big, little, len) == 0)
			return ((char *)big);
		big++;
		n--;
	}
	return (NULL);
}
