/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = dst;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			i;

	if (size && count > (size_t)-1 / size)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	i = 0;
	while (i < count * size)
		p[i++] = 0;
	return (p);
}
