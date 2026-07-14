/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static const char	*base_name(const char *path)
{
	const char	*last;
	const char	*p;

	last = path;
	p = path;
	while (*p)
	{
		if (*p == '/' && p[1])
			last = p + 1;
		p++;
	}
	return (last);
}

int	make_entry(t_entry *entry, const char *path)
{
	if (lstat(path, &entry->st) < 0)
		return (0);
	entry->name = ft_strdup(base_name(path));
	entry->path = ft_strdup(path);
	if (!entry->name || !entry->path)
		fatal_alloc();
	return (1);
}
