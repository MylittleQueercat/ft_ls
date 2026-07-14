/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dev	device_major(dev_t device)
{
	return ((unsigned long)major(device));
}

t_dev	device_minor(dev_t device)
{
	return ((unsigned long)minor(device));
}

static void	put_device(t_entry *entry, t_widths *widths)
{
	char	*major_value;
	char	*minor_value;
	size_t	device_width;

	major_value = ft_ulltoa(device_major(entry->st.st_rdev));
	minor_value = ft_ulltoa(device_minor(entry->st.st_rdev));
	device_width = widths->major + widths->minor + 2;
	ft_putpad_fd(device_width, widths->size, 1);
	ft_putpad_fd(ft_strlen(major_value), widths->major, 1);
	ft_putstr_fd(major_value, 1);
	ft_putstr_fd(", ", 1);
	ft_putpad_fd(ft_strlen(minor_value), widths->minor, 1);
	ft_putstr_fd(minor_value, 1);
	free(major_value);
	free(minor_value);
}

void	put_size_field(t_entry *entry, t_widths *widths)
{
	char	*num;

	if (S_ISCHR(entry->st.st_mode) || S_ISBLK(entry->st.st_mode))
		put_device(entry, widths);
	else
	{
		num = ft_ulltoa(entry->st.st_size);
		ft_putpad_fd(ft_strlen(num), widths->size, 1);
		ft_putstr_fd(num, 1);
		free(num);
	}
}
