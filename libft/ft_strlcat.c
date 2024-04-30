/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:32:02 by danevans          #+#    #+#             */
/*   Updated: 2023/07/20 11:55:06 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	dst_len = 0;
	src_len = 0;
	while (dst[dst_len] != '\0')
		dst_len++;
	while (src[i] != '\0')
		i++;
	if (size <= dst_len)
		return (size + i);
	while (src[src_len] != '\0' && dst_len < size - 1)
	{
		dst[dst_len + src_len] = src[src_len];
		src_len++;
		size--;
	}
	dst[dst_len + src_len] = '\0';
	return (dst_len + i);
}
