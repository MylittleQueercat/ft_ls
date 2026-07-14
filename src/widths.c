/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	number_width(unsigned long long value)
{
	size_t	width;

	width = 1;
	while (value >= 10)
	{
		value /= 10;
		width++;
	}
	return (width);
}

static void	identity_widths(t_entry *entry, t_widths *widths)
{
	size_t	width;

	cache_identity_names(entry, widths);
	width = ft_strlen(entry->owner);
	if (width > widths->owner)
		widths->owner = width;
	width = ft_strlen(entry->group);
	if (width > widths->group)
		widths->group = width;
}

static void	device_widths(t_entry *entry, t_widths *widths)
{
	size_t	width;

	if (!S_ISCHR(entry->st.st_mode) && !S_ISBLK(entry->st.st_mode))
		return ;
	width = number_width(device_major(entry->st.st_rdev));
	if (width > widths->major)
		widths->major = width;
	width = number_width(device_minor(entry->st.st_rdev));
	if (width > widths->minor)
		widths->minor = width;
}

void	calculate_widths(t_list *list, t_widths *widths)
{
	t_entry	*entry;
	size_t	i;
	size_t	width;

	*widths = (t_widths){0};
	i = 0;
	while (i < list->len)
	{
		entry = &list->items[i++];
		width = number_width(entry->st.st_nlink);
		if (width > widths->links)
			widths->links = width;
		width = number_width(entry->st.st_size);
		if (width > widths->size)
			widths->size = width;
		identity_widths(entry, widths);
		device_widths(entry, widths);
	}
	width = widths->major + widths->minor + 2;
	if (width > widths->size && widths->major)
		widths->size = width;
}
