/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	put_owner(t_entry *entry, t_widths *widths)
{
	ft_putstr_fd(entry->owner, 1);
	ft_putpad_fd(ft_strlen(entry->owner), widths->owner, 1);
}

static void	put_group(t_entry *entry, t_widths *widths)
{
	ft_putstr_fd(entry->group, 1);
	ft_putpad_fd(ft_strlen(entry->group), widths->group, 1);
}

void	put_long_identity(t_entry *entry, t_widths *widths, t_opts *opts)
{
	char	mode[11];
	char	*num;

	mode_string(entry->st.st_mode, mode);
	ft_putstr_fd(mode, 1);
	ft_putchar_fd(' ', 1);
	num = ft_ulltoa(entry->st.st_nlink);
	ft_putpad_fd(ft_strlen(num), widths->links, 1);
	ft_putnbr_fd(entry->st.st_nlink, 1);
	free(num);
	ft_putchar_fd(' ', 1);
	if (!opts->g)
	{
		put_owner(entry, widths);
		ft_putchar_fd(' ', 1);
	}
	put_group(entry, widths);
	ft_putchar_fd(' ', 1);
}
