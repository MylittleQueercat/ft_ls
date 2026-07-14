/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		g_output[8192];
static size_t	g_output_len;

void	ft_putstr_fd(const char *s, int fd)
{
	size_t	length;
	size_t	chunk;

	if (!s)
		return ;
	length = ft_strlen(s);
	if (fd != 1)
		return ((void)write(fd, s, length));
	while (length)
	{
		chunk = sizeof(g_output) - g_output_len;
		if (chunk > length)
			chunk = length;
		ft_memcpy(g_output + g_output_len, s, chunk);
		g_output_len += chunk;
		s += chunk;
		length -= chunk;
		if (g_output_len == sizeof(g_output))
			ft_flush();
	}
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd != 1)
		write(fd, &c, 1);
	else
	{
		g_output[g_output_len++] = c;
		if (g_output_len == sizeof(g_output))
			ft_flush();
	}
}

void	ft_putnbr_fd(long long n, int fd)
{
	unsigned long long	u;
	char				c;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		u = (unsigned long long)(-(n + 1)) + 1;
	}
	else
		u = (unsigned long long)n;
	if (u >= 10)
		ft_putnbr_fd((long long)(u / 10), fd);
	c = (char)('0' + u % 10);
	ft_putchar_fd(c, fd);
}

void	ft_putpad_fd(size_t used, size_t width, int fd)
{
	while (used++ < width)
		ft_putchar_fd(' ', fd);
}

void	ft_flush(void)
{
	if (g_output_len)
		write(1, g_output, g_output_len);
	g_output_len = 0;
}
