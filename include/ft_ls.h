/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 00:00:00 by leticiabi         #+#    #+#             */
/*   Updated: 2026/07/14 00:00:00 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>
# include <sys/stat.h>
# include <string.h>
# include <sys/ioctl.h>
# include <time.h>
# ifndef __APPLE__
#  include <sys/sysmacros.h>
# endif

typedef struct s_opts
{
	int	l;
	int	r_upper;
	int	a;
	int	r;
	int	t;
	int	one;
	int	u;
	int	f;
	int	g;
	int	d;
}	t_opts;

typedef struct s_entry
{
	char			*name;
	char			*path;
	char			*owner;
	char			*group;
	struct stat		st;
}	t_entry;

typedef struct s_list
{
	t_entry	*items;
	size_t	len;
	size_t	cap;
}	t_list;

typedef struct s_ctx
{
	t_opts	opts;
	int		error;
	int		printed;
}	t_ctx;

typedef struct s_widths
{
	size_t	links;
	size_t	owner;
	size_t	group;
	size_t	size;
	size_t	major;
	size_t	minor;
	uid_t	uid;
	gid_t	gid;
	char	*owner_cache;
	char	*group_cache;
}	t_widths;

typedef unsigned long	t_dev;

int		parse_args(int ac, char **av, t_opts *opts, int *first);
void	fatal_alloc(void);
void	print_error(const char *name);
void	print_dir_error(const char *name);
char	*path_join(const char *left, const char *right);
int		list_add(t_list *list, const char *name, const char *path,
			struct stat *st);
int		list_add_owned(t_list *list, const char *name, char *path,
			struct stat *st);
void	list_free(t_list *list);
int		make_entry(t_entry *entry, const char *path);
void	sort_list(t_list *list, t_opts *opts);
long	entry_nsec(t_entry *entry, int access_time);
time_t	entry_time(t_entry *entry, int access_time);
void	display_entries(t_list *list, t_ctx *ctx, int directory);
void	display_columns(t_list *list);
void	display_long(t_entry *entry, t_widths *widths, t_opts *opts);
void	put_long_identity(t_entry *entry, t_widths *widths, t_opts *opts);
void	put_size_field(t_entry *entry, t_widths *widths);
t_dev	device_major(dev_t device);
t_dev	device_minor(dev_t device);
void	calculate_widths(t_list *list, t_widths *widths);
void	cache_identity_names(t_entry *entry, t_widths *widths);
void	mode_string(mode_t mode, char out[11]);
void	process_operands(int count, char **paths, t_ctx *ctx);
void	process_directory(const char *path, t_ctx *ctx, int header);

#endif
