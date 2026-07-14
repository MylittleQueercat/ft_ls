/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	put_time(time_t stamp)
{
	char	*value;
	time_t	now;
	int		i;

	value = ctime(&stamp);
	now = time(NULL);
	if (!value)
		return (ft_putstr_fd("??? ?? ????", 1));
	i = 4;
	while (i < 11)
		ft_putchar_fd(value[i++], 1);
	if (stamp > now + 3600 || now - stamp > 15778476)
	{
		ft_putchar_fd(' ', 1);
		i = 20;
		while (i < 24)
			ft_putchar_fd(value[i++], 1);
	}
	else
	{
		i = 11;
		while (i < 16)
			ft_putchar_fd(value[i++], 1);
	}
}

static void	put_link(t_entry *entry)
{
	char	*target;
	ssize_t	n;

	if (!S_ISLNK(entry->st.st_mode))
		return ;
	target = malloc(4097);
	if (!target)
		fatal_alloc();
	n = readlink(entry->path, target, 4096);
	if (n >= 0)
	{
		target[n] = '\0';
		ft_putstr_fd(" -> ", 1);
		ft_putstr_fd(target, 1);
	}
	free(target);
}

void	display_long(t_entry *entry, t_widths *widths, t_opts *opts)
{
	put_long_identity(entry, widths, opts);
	put_size_field(entry, widths);
	ft_putchar_fd(' ', 1);
	put_time(entry_time(entry, opts->u));
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(entry->name, 1);
	put_link(entry);
	ft_putchar_fd('\n', 1);
}
