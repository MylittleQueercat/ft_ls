/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_cache.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	cache_owner(t_entry *entry, t_widths *widths)
{
	struct passwd	*pw;

	if (widths->owner_cache && widths->uid == entry->st.st_uid)
		entry->owner = ft_strdup(widths->owner_cache);
	else
	{
		pw = getpwuid(entry->st.st_uid);
		if (pw)
			entry->owner = ft_strdup(pw->pw_name);
		else
			entry->owner = ft_ulltoa(entry->st.st_uid);
		widths->uid = entry->st.st_uid;
		widths->owner_cache = entry->owner;
	}
}

static void	cache_group(t_entry *entry, t_widths *widths)
{
	struct group	*gr;

	if (widths->group_cache && widths->gid == entry->st.st_gid)
		entry->group = ft_strdup(widths->group_cache);
	else
	{
		gr = getgrgid(entry->st.st_gid);
		if (gr)
			entry->group = ft_strdup(gr->gr_name);
		else
			entry->group = ft_ulltoa(entry->st.st_gid);
		widths->gid = entry->st.st_gid;
		widths->group_cache = entry->group;
	}
}

void	cache_identity_names(t_entry *entry, t_widths *widths)
{
	cache_owner(entry, widths);
	cache_group(entry, widths);
	if (!entry->owner || !entry->group)
		fatal_alloc();
}
