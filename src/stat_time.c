/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#ifdef __APPLE__

long	entry_nsec(t_entry *entry, int access_time)
{
	if (access_time)
		return (entry->st.st_atimespec.tv_nsec);
	return (entry->st.st_mtimespec.tv_nsec);
}

#else

long	entry_nsec(t_entry *entry, int access_time)
{
	if (access_time)
		return (entry->st.st_atim.tv_nsec);
	return (entry->st.st_mtim.tv_nsec);
}

#endif

time_t	entry_time(t_entry *entry, int access_time)
{
	if (access_time)
		return (entry->st.st_atime);
	return (entry->st.st_mtime);
}
