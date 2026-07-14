/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*path_join(const char *left, const char *right)
{
	size_t	a;
	size_t	b;
	char	*out;
	int		slash;

	a = ft_strlen(left);
	b = ft_strlen(right);
	slash = (a > 0 && left[a - 1] != '/');
	out = malloc(a + b + slash + 1);
	if (!out)
		fatal_alloc();
	ft_memcpy(out, left, a);
	if (slash)
		out[a++] = '/';
	ft_memcpy(out + a, right, b + 1);
	return (out);
}
