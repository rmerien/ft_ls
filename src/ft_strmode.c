/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:01:01 by rmerien           #+#    #+#             */
/*   Updated: 2018/12/11 05:04:01 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>

static char		ft_get_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISWHT(mode))
		return ('w');
	return ('?');
}

static char		ft_get_acl(char *path)
{
	acl_t	check;
	char	*buf;

	buf = NULL;
	if (listxattr(path, buf, sizeof(buf), XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((check = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
		return (acl_free(check) ? '!' : '+');
	return (' ');
}

char			*ft_strmode(mode_t mode, char *path)
{
	char	bp[12];

	bp[0] = ft_get_type(mode);
	bp[1] = (S_IRUSR & mode) ? 'r' : '-';
	bp[2] = (S_IWUSR & mode) ? 'w' : '-';
	bp[3] = (S_IXUSR & mode) ? 'x' : '-';
	if (S_ISUID & mode)
		bp[3] = (bp[3] == '-' ? 'S' : 's');
	bp[4] = (S_IRGRP & mode) ? 'r' : '-';
	bp[5] = (S_IWGRP & mode) ? 'w' : '-';
	bp[6] = (S_IXGRP & mode) ? 'x' : '-';
	if (S_ISGID & mode)
		bp[6] = (bp[6] == '-' ? 'S' : 's');
	bp[7] = (S_IROTH & mode) ? 'r' : '-';
	bp[8] = (S_IWOTH & mode) ? 'w' : '-';
	bp[9] = (S_IXOTH & mode) ? 'x' : '-';
	if (S_ISVTX & mode)
		bp[9] = (bp[9] == '-' ? 'T' : 't');
	bp[10] = ft_get_acl(path);
	bp[11] = '\0';
	return (ft_strdup(bp));
}
