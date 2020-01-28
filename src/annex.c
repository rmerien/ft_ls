/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 02:39:23 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/11 05:02:48 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/dir.h>
#include <errno.h>
#include "ft_ls.h"
#include "ft_printf.h"

/*
** Function that returns a new file_path with the name of the next file to be
** checked appended to the previous path
*/

char	*ft_get_next_path(char *current_path, t_list *file)
{
	char	*result;

	if (file == NULL)
		return (ft_strdup(current_path));
	result = ft_strjoin(current_path,
		ft_strrchr(((t_file *)(file->content))->path, '/'));
	return (result);
}

/*
** Function that does the same work as the previous one, except that it works
** on two C-strings and no file structure
*/

char	*ft_append_str_slash(char *path_to_list, char *s2)
{
	char	*result;
	char	*tmp;

	tmp = ft_strjoin(path_to_list, "/");
	result = ft_strjoin(tmp, s2);
	ft_strdel(&tmp);
	return (result);
}

/*
** This function is responsible of checking if a specified
** file path is corresponding to a directory
*/

int		ft_is_dir(char *current_path, t_list *file, int check_point)
{
	DIR			*dir;
	char		*path;
	char		*catch;

	dir = NULL;
	catch = NULL;
	path = ft_get_next_path(current_path, file);
	if (check_point &&
		(((catch = ft_strrstr(path, "/..")) != NULL && *(catch + 3) == '\0')
		|| ((catch = ft_strrstr(path, "/.")) != NULL && *(catch + 2) == '\0')))
	{
		free(path);
		return (0);
	}
	if ((dir = opendir(path)) != NULL)
		closedir(dir);
	free(path);
	if (dir != NULL)
		return (1);
	return (errno == EACCES);
}
