/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 03:43:06 by danevans          #+#    #+#             */
/*   Updated: 2023/07/22 11:20:57 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*destcast;
	const char	*srccast;
	size_t		i;

	destcast = (char *)dest;
	srccast = (const char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (srccast < destcast)
	{
		i = n;
		while (i > 0)
		{
			destcast[i - 1] = srccast[i - 1];
			i--;
		}
	}
	else
		ft_memcpy(destcast, srccast, n);
	return (dest);
}
