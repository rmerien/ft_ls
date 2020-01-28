/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:32:35 by rmerien           #+#    #+#             */
/*   Updated: 2018/12/11 05:07:19 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include "ft_ls.h"
#include "ft_printf.h"

static char	*date_str(long seconds)
{
	char	*str;
	char	*date;
	int		i;

	i = -1;
	if (!(str = (char*)malloc(sizeof(char) * 13)))
		return (0);
	date = ft_strdup(ctime(&seconds));
	str[12] = '\0';
	while (++i < 6)
		str[i] = date[i + 4];
	str[i] = ' ';
	if (time(NULL) < (seconds - SIX_MONTHS)
		|| time(NULL) > (seconds + SIX_MONTHS))
	{
		while (++i < 12)
			str[i] = date[i + 12];
	}
	else
		while (++i < 12)
			str[i] = date[i + 4];
	free(date);
	return (str);
}

static char	*get_date(t_file data, int opt)
{
	char *result;

	if (opt >> BU_INDEX & 1)
		result = date_str(data.infos.st_birthtimespec.tv_sec);
	else
		result = date_str(data.infos.st_mtimespec.tv_sec);
	return (result);
}

void		opt_l(t_file data, int opt, t_max vroum)
{
	struct passwd	*pw;
	struct group	*gr;
	char			*date;
	char			buf[256];
	char			*modes;

	ft_bzero(buf, 256);
	data.short_path = ft_strrchr(data.path, '/')
		? ft_strrchr(data.path, '/') + 1 : data.path;
	pw = getpwuid(data.infos.st_uid);
	gr = getgrgid(data.infos.st_gid);
	modes = ft_strmode(data.infos.st_mode, data.path);
	date = get_date(data, opt);
	ft_printf("%s %*d %-*s %-*s", modes, vroum.nl, data.infos.st_nlink, vroum.pw
		, pw->pw_name, vroum.gr, opt >> SO_INDEX & 1 ? "" : gr->gr_name);
	(modes[0] == 'c' || modes[0] == 'b')
	? ft_printf("%4u,%4u", major(data.infos.st_rdev),
		minor(data.infos.st_rdev))
	: ft_printf("%*lld", vroum.size, data.infos.st_size);
	ft_printf(" %s ", date);
	ft_colored_name(data.short_path, data.infos.st_mode, opt);
	readlink(data.path, buf, 255) > 0 ? ft_printf(" -> %s\n", buf)
		: write(1, "\n", 1);
	ft_strdel(&modes);
	ft_strdel(&date);
}
