/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	is_dot_dir(const char *name)
{
	return (ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0);
}

static void	put_total(t_list *list)
{
	size_t		i;
	long long	blocks;

	i = 0;
	blocks = 0;
	while (i < list->len)
		blocks += list->items[i++].st.st_blocks;
	ft_putstr_fd("total ", 1);
	ft_putnbr_fd(blocks / 2, 1);
	ft_putchar_fd('\n', 1);
}

static void	recurse_entries(t_list *list, t_ctx *ctx)
{
	size_t	i;
	t_entry	*entry;

	i = 0;
	while (i < list->len)
	{
		entry = &list->items[i++];
		if (S_ISDIR(entry->st.st_mode) && !is_dot_dir(entry->name))
			process_directory(entry->path, ctx, 1);
	}
}

static void	display_names(t_list *list, t_ctx *ctx)
{
	size_t	i;

	if (!ctx->opts.one && isatty(STDOUT_FILENO))
		return (display_columns(list));
	i = 0;
	while (i < list->len)
	{
		ft_putstr_fd(list->items[i].name, 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	display_entries(t_list *list, t_ctx *ctx, int directory)
{
	t_widths	widths;
	size_t		i;

	if (ctx->opts.l && directory)
		put_total(list);
	if (ctx->opts.l)
		calculate_widths(list, &widths);
	i = 0;
	if (!ctx->opts.l)
		display_names(list, ctx);
	while (ctx->opts.l && i < list->len)
	{
		display_long(&list->items[i], &widths, &ctx->opts);
		i++;
	}
	ctx->printed = 1;
	if (ctx->opts.r_upper && directory)
		recurse_entries(list, ctx);
}
