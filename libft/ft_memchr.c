/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:13:30 by danevans          #+#    #+#             */
/*   Updated: 2023/07/20 11:40:35 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*strcast;
	unsigned char		value;

	strcast = (const unsigned char *)s;
	value = (unsigned char)c;
	while (n > 0)
	{
		if (*strcast == value)
			return ((void *)strcast);
		n--;
		strcast++;
	}
	return (NULL);
}
