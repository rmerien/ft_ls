/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 07:38:21 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/11 05:17:35 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/dir.h>
#include <errno.h>
#include "ft_ls.h"
#include "ft_printf.h"

int					ft_is_symlink(char *path)
{
	int			ret;
	struct stat	buf;

	if ((ret = lstat(path, &buf) == 0))
	{
		if (S_ISLNK(buf.st_mode))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

static t_list		*ft_del_list(t_list **head)
{
	t_list	*curr;
	t_list	*tmp;

	curr = *head;
	while (curr)
	{
		tmp = curr->next;
		free(((t_file *)(curr->content))->path);
		free((t_file *)curr->content);
		free(curr);
		curr = tmp;
	}
	*head = NULL;
	return (NULL);
}

static t_file		*get_file(char *path)
{
	t_file		*result;
	struct stat	buf;

	if ((result = (t_file *)ft_memalloc(sizeof(t_file))) == NULL)
		return (NULL);
	result->path = ft_strdup(path);
	result->valid = (lstat(path, &buf) == 0);
	result->infos = buf;
	if (result->valid == 1)
		return (result);
	else
	{
		free(result->path);
		free(result);
		return (NULL);
	}
}

int					ft_add_file(t_list **result, char *path)
{
	t_file	*to_add;
	char	*catch;

	if (errno != 13 && (to_add = get_file(path)) != NULL)
	{
		ft_lstadd(result, ft_lstnew(to_add, sizeof(t_file)));
		free(to_add);
		ft_strdel(&path);
		return (1);
	}
	else
	{
		catch = ft_strrchr(path, '/');
		catch = catch ? catch : path;
		write(2, "./ft_ls: ", 9);
		write(2, catch, ft_strlen(catch));
		if (errno == ENOENT)
			write(2, ": No such file or directory\n", 28);
		else if (errno == EACCES)
			write(2, ": Permission denied\n", 20);
		else
			write(2, ": Undefined error\n", 18);
		ft_strdel(&path);
		return (0);
	}
}

t_list				*ft_get_files(char *path_to_list)
{
	DIR				*dir;
	t_list			*result;
	struct dirent	*sd;

	result = NULL;
	errno = 0;
	if ((dir = opendir(path_to_list)) == NULL || ft_is_symlink(path_to_list))
		ft_add_file(&result, ft_strdup(path_to_list));
	else
		while ((sd = readdir(dir)) != NULL)
		{
			if (!ft_add_file(&result,
				ft_append_str_slash(path_to_list, sd->d_name)))
			{
				ft_strdel(&path_to_list);
				return (ft_del_list(&result));
			}
		}
	if (dir != NULL)
		closedir(dir);
	return (result);
}
