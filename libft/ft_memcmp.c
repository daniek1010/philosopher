/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:23:01 by danevans          #+#    #+#             */
/*   Updated: 2023/07/20 12:01:07 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*dst;
	const unsigned char	*src;

	dst = (const unsigned char *)s1;
	src = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*dst != *src)
			return (*dst - *src);
		n--;
		dst++;
		src++;
	}
	return (0);
}
