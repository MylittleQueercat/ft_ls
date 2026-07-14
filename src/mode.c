/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	file_type(mode_t mode)
{
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	return ('-');
}

static void	special_bits(mode_t mode, char out[11])
{
	if (mode & S_ISUID)
		out[3] = ((mode & S_IXUSR) != 0) * ('s' - 'S') + 'S';
	if (mode & S_ISGID)
		out[6] = ((mode & S_IXGRP) != 0) * ('s' - 'S') + 'S';
	if (mode & S_ISVTX)
		out[9] = ((mode & S_IXOTH) != 0) * ('t' - 'T') + 'T';
}

void	mode_string(mode_t mode, char out[11])
{
	static mode_t	bits[9] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP,
		S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	static char		chars[3] = {'r', 'w', 'x'};
	int				i;

	out[0] = file_type(mode);
	i = 0;
	while (i < 9)
	{
		out[i + 1] = '-';
		if (mode & bits[i])
			out[i + 1] = chars[i % 3];
		i++;
	}
	out[10] = '\0';
	special_bits(mode, out);
}
