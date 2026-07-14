/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fatal_alloc(void)
{
	ft_flush();
	ft_putstr_fd("ft_ls: memory allocation failed\n", 2);
	exit(1);
}

void	print_error(const char *name)
{
	ft_putstr_fd("ft_ls: cannot access '", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void	print_dir_error(const char *name)
{
	ft_putstr_fd("ft_ls: cannot open directory '", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}
