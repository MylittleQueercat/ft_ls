/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	collect_operands(int count, char **paths, t_list *list,
		t_ctx *ctx)
{
	struct stat	st;
	int			i;

	i = 0;
	while (i < count)
	{
		if (lstat(paths[i], &st) < 0)
		{
			print_error(paths[i]);
			ctx->error = 1;
		}
		else
			list_add(list, paths[i], paths[i], &st);
		i++;
	}
}

static void	display_files(t_list *list, t_ctx *ctx)
{
	t_list	files;
	size_t	i;

	files = (t_list){0};
	i = 0;
	while (i < list->len)
	{
		if (!S_ISDIR(list->items[i].st.st_mode) || ctx->opts.d)
			list_add(&files, list->items[i].name, list->items[i].path,
				&list->items[i].st);
		i++;
	}
	if (files.len)
		display_entries(&files, ctx, 0);
	list_free(&files);
}

static void	display_long_files(t_list *list, t_ctx *ctx)
{
	t_widths	widths;
	size_t		i;

	calculate_widths(list, &widths);
	i = 0;
	while (i < list->len)
	{
		if (!S_ISDIR(list->items[i].st.st_mode) || ctx->opts.d)
		{
			display_long(&list->items[i], &widths, &ctx->opts);
			ctx->printed = 1;
		}
		i++;
	}
}

static void	display_directories(t_list *list, t_ctx *ctx, int header)
{
	size_t	i;

	i = 0;
	while (i < list->len)
	{
		if (S_ISDIR(list->items[i].st.st_mode) && !ctx->opts.d)
			process_directory(list->items[i].path, ctx, header);
		i++;
	}
}

void	process_operands(int count, char **paths, t_ctx *ctx)
{
	t_list	list;
	int		header;

	list = (t_list){0};
	collect_operands(count, paths, &list, ctx);
	sort_list(&list, &ctx->opts);
	if (ctx->opts.l)
		display_long_files(&list, ctx);
	else
		display_files(&list, ctx);
	header = (count > 1 || ctx->opts.r_upper);
	display_directories(&list, ctx, header);
	list_free(&list);
}
