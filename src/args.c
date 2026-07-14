/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	set_bonus(char c, t_opts *opts)
{
	if (c == 'u')
		opts->u = 1;
	else if (c == 'f')
	{
		opts->f = 1;
		opts->a = 1;
	}
	else if (c == 'g')
	{
		opts->g = 1;
		opts->l = 1;
	}
	else if (c == 'd')
		opts->d = 1;
	else
		return (0);
	return (1);
}

static int	set_option(char c, t_opts *opts)
{
	if (c == 'l')
		opts->l = 1;
	else if (c == 'R')
		opts->r_upper = 1;
	else if (c == 'a')
		opts->a = 1;
	else if (c == 'r')
		opts->r = 1;
	else if (c == 't')
	{
		opts->t = 1;
		opts->f = 0;
	}
	else if (c == '1')
		opts->one = 1;
	else
		return (set_bonus(c, opts));
	return (1);
}

static void	invalid_option(char c)
{
	ft_putstr_fd("ft_ls: invalid option -- '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\nTry 'ft_ls --help' for more information.\n", 2);
}

int	parse_args(int ac, char **av, t_opts *opts, int *first)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1])
	{
		if (ft_strcmp(av[i], "--") == 0)
		{
			i++;
			break ;
		}
		j = 1;
		while (av[i][j])
			if (!set_option(av[i][j++], opts))
				return (invalid_option(av[i][j - 1]), 0);
		i++;
	}
	*first = i;
	return (1);
}
