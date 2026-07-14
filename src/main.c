/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	add_dirent(const char *path, struct dirent *de, t_list *list,
		t_ctx *ctx)
{
	struct stat	st;
	char		*full;

	if (!ctx->opts.a && de->d_name[0] == '.')
		return ;
	full = path_join(path, de->d_name);
	if (lstat(full, &st) == 0)
		list_add_owned(list, de->d_name, full, &st);
	else
	{
		print_error(full);
		ctx->error = 1;
		free(full);
	}
}

static int	read_directory(const char *path, t_list *list, t_ctx *ctx)
{
	DIR				*dir;
	struct dirent	*de;

	dir = opendir(path);
	if (!dir)
		return (print_dir_error(path), ctx->error = 1, 0);
	errno = 0;
	de = readdir(dir);
	while (de)
	{
		add_dirent(path, de, list, ctx);
		de = readdir(dir);
	}
	if (errno)
		(print_error(path), ctx->error = 1);
	closedir(dir);
	return (1);
}

void	process_directory(const char *path, t_ctx *ctx, int header)
{
	t_list	list;

	list = (t_list){0};
	if (header)
	{
		if (ctx->printed)
			ft_putchar_fd('\n', 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(":\n", 1);
		ctx->printed = 1;
	}
	if (!read_directory(path, &list, ctx))
		return ;
	sort_list(&list, &ctx->opts);
	display_entries(&list, ctx, 1);
	list_free(&list);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;
	char	*dot;
	int		first;

	ctx = (t_ctx){0};
	if (!parse_args(ac, av, &ctx.opts, &first))
		return (1);
	dot = ".";
	if (first == ac)
	{
		if (ctx.opts.d)
			process_operands(1, &dot, &ctx);
		else
			process_directory(".", &ctx, ctx.opts.r_upper);
	}
	else
		process_operands(ac - first, av + first, &ctx);
	ft_flush();
	return (ctx.error);
}
