/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ulltoa(unsigned long long n)
{
	char		buf[32];
	char		*out;
	int			i;
	int			j;

	i = 31;
	buf[i--] = '\0';
	if (n == 0)
		buf[i--] = '0';
	while (n)
	{
		buf[i--] = (char)('0' + n % 10);
		n /= 10;
	}
	out = malloc(31 - i);
	if (!out)
		return (NULL);
	j = 0;
	while (++i < 32)
		out[j++] = buf[i];
	return (out);
}
