/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	name_order(t_entry *a, t_entry *b)
{
	return (ft_strcmp(a->name, b->name));
}

static int	time_order(t_entry *a, t_entry *b, t_opts *opts)
{
	if (entry_time(a, opts->u) > entry_time(b, opts->u))
		return (-1);
	if (entry_time(a, opts->u) < entry_time(b, opts->u))
		return (1);
	if (entry_nsec(a, opts->u) > entry_nsec(b, opts->u))
		return (-1);
	if (entry_nsec(a, opts->u) < entry_nsec(b, opts->u))
		return (1);
	return (name_order(a, b));
}

static int	compare(t_entry *a, t_entry *b, t_opts *opts)
{
	int	value;

	if (opts->t)
		value = time_order(a, b, opts);
	else
		value = name_order(a, b);
	if (opts->r)
		value = -value;
	return (value);
}

void	sort_list(t_list *list, t_opts *opts)
{
	size_t	i;
	size_t	j;
	t_entry	key;

	if (opts->f)
		return ;
	i = 1;
	while (i < list->len)
	{
		key = list->items[i];
		j = i;
		while (j > 0 && compare(&list->items[j - 1], &key, opts) > 0)
		{
			list->items[j] = list->items[j - 1];
			j--;
		}
		list->items[j] = key;
		i++;
	}
}
