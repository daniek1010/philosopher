/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 02:44:50 by danevans          #+#    #+#             */
/*   Updated: 2023/07/22 11:26:11 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*destcast;
	const char	*srccast;

	if (dest == NULL && src == NULL)
		return (NULL);
	destcast = (char *)dest;
	srccast = (const char *)src;
	i = 0;
	while (i < n)
	{
		destcast[i] = srccast[i];
		i++;
	}
	return (dest);
}
