/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:39:35 by danevans          #+#    #+#             */
/*   Updated: 2023/07/22 15:36:27 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	if (c > 128)
		c = c % 128;
	last = NULL;
	while (*s != '\0')
	{
		if (*s == c)
			last = s;
		s++;
	}
	if (*s == c)
		last = s;
	return ((char *)last);
}
