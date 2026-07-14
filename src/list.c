/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	grow_list(t_list *list)
{
	t_entry	*items;
	size_t	new_cap;

	new_cap = list->cap * 2;
	if (new_cap == 0)
		new_cap = 16;
	items = malloc(new_cap * sizeof(t_entry));
	if (!items)
		fatal_alloc();
	if (list->items)
		ft_memcpy(items, list->items, list->len * sizeof(t_entry));
	free(list->items);
	list->items = items;
	list->cap = new_cap;
}

int	list_add(t_list *list, const char *name, const char *path,
	struct stat *st)
{
	t_entry	*entry;

	if (list->len == list->cap)
		grow_list(list);
	entry = &list->items[list->len];
	entry->name = ft_strdup(name);
	entry->path = ft_strdup(path);
	if (!entry->name || !entry->path)
		fatal_alloc();
	entry->st = *st;
	entry->owner = NULL;
	entry->group = NULL;
	list->len++;
	return (1);
}

int	list_add_owned(t_list *list, const char *name, char *path,
	struct stat *st)
{
	t_entry	*entry;

	if (list->len == list->cap)
		grow_list(list);
	entry = &list->items[list->len];
	entry->name = ft_strdup(name);
	if (!entry->name)
		fatal_alloc();
	entry->path = path;
	entry->st = *st;
	entry->owner = NULL;
	entry->group = NULL;
	list->len++;
	return (1);
}

void	list_free(t_list *list)
{
	size_t	i;

	i = 0;
	while (i < list->len)
	{
		free(list->items[i].name);
		free(list->items[i].path);
		free(list->items[i].owner);
		free(list->items[i].group);
		i++;
	}
	free(list->items);
	list->items = NULL;
	list->len = 0;
	list->cap = 0;
}
