/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_max.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 03:12:26 by rmerien           #+#    #+#             */
/*   Updated: 2018/12/11 05:03:38 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>

static t_max	ft_initiate(void)
{
	t_max	scoot;

	scoot.nl = 0;
	scoot.pw = 0;
	scoot.gr = 0;
	scoot.size = 0;
	scoot.total = 0;
	return (scoot);
}

static void		fill(struct stat data, t_max *scoot)
{
	int				tmp;
	struct passwd	*pw;
	struct group	*gr;

	pw = getpwuid(data.st_uid);
	gr = getgrgid(data.st_gid);
	if ((tmp = ft_nblen((long long)data.st_nlink)) > scoot->nl)
		scoot->nl = tmp;
	if ((tmp = (int)ft_strlen(pw->pw_name)) > scoot->pw)
		scoot->pw = tmp + 1;
	if ((tmp = (int)ft_strlen(gr->gr_name)) > scoot->gr)
		scoot->gr = tmp + 1;
	if ((tmp = ft_nblen(data.st_size)) > scoot->size)
		scoot->size = tmp + 1;
	scoot->total += data.st_blocks;
}

t_max			ft_fill_max(t_list *list, int opt)
{
	t_max	scoot;
	char	*name;

	scoot = ft_initiate();
	while (list)
	{
		name = ft_strrchr(((t_file *)(list->content))->path, '/');
		name = name ? name + 1 : ((t_file *)(list->content))->path;
		if (*name != '.' || opt >> SA_INDEX & 1)
			fill(((t_file *)(list->content))->infos, &scoot);
		list = list->next;
	}
	return (scoot);
}
