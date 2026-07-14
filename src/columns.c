/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   columns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	column_width(t_list *list, size_t start, size_t rows)
{
	size_t	width;
	size_t	length;
	size_t	i;

	width = 0;
	i = start;
	while (i < list->len)
	{
		length = ft_strlen(list->items[i].name);
		if (length > width)
			width = length;
		i++;
		if (i >= start + rows)
			break ;
	}
	return (width);
}

static size_t	layout_width(t_list *list, size_t rows)
{
	size_t	columns;
	size_t	column;
	size_t	width;

	columns = (list->len + rows - 1) / rows;
	column = 0;
	width = 0;
	while (column < columns)
	{
		width += column_width(list, column * rows, rows);
		if (column + 1 < columns)
			width += 2;
		column++;
	}
	return (width);
}

static void	put_cell(t_list *list, size_t index, size_t column, size_t rows)
{
	size_t	width;

	if (index >= list->len)
		return ;
	ft_putstr_fd(list->items[index].name, 1);
	if (index + rows < list->len)
	{
		width = column_width(list, column * rows, rows) + 2;
		ft_putpad_fd(ft_strlen(list->items[index].name), width, 1);
	}
}

static void	put_grid(t_list *list, size_t rows)
{
	size_t	columns;
	size_t	row;
	size_t	column;
	size_t	index;

	columns = (list->len + rows - 1) / rows;
	row = 0;
	while (row < rows)
	{
		column = 0;
		while (column < columns)
		{
			index = row + column * rows;
			put_cell(list, index, column, rows);
			column++;
		}
		ft_putchar_fd('\n', 1);
		row++;
	}
}

void	display_columns(t_list *list)
{
	struct winsize	window;
	size_t			terminal;
	size_t			rows;

	if (!list->len)
		return ;
	terminal = 80;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window) == 0 && window.ws_col)
		terminal = window.ws_col;
	rows = 1;
	while (rows < list->len && layout_width(list, rows) > terminal)
		rows++;
	put_grid(list, rows);
}
