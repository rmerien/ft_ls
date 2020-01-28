/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 05:43:46 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/11 05:25:25 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "ft_ls.h"
#include "ft_printf.h"

static void	ft_format_long(t_list *files, t_ls ls_inf)
{
	char	*name;
	t_max	scoot;

	scoot = ft_fill_max(files, ls_inf.opt);
	if (S_ISDIR(((t_file *)(files->content))->infos.st_mode))
		ft_printf("total %d\n", scoot.total);
	while (files)
	{
		name = ft_strrchr(((t_file *)(files->content))->path, '/');
		name = name ? name + 1 : ((t_file *)(files->content))->path;
		if (*name != '.' || (ls_inf.opt >> SA_INDEX & 1))
			opt_l(*((t_file *)(files->content)), ls_inf.opt, scoot);
		files = files->next;
	}
}

static void	ft_format_short(t_list *files, t_ls ls_inf)
{
	char *name;

	while (files)
	{
		name = ft_strrchr(((t_file *)(files->content))->path, '/');
		name = name ? name + 1 : ((t_file *)(files->content))->path;
		if (*name != '.' || (ls_inf.opt >> SA_INDEX & 1))
		{
			ft_colored_name(name,
				((t_file *)(files->content))->infos.st_mode, ls_inf.opt);
			ft_putchar('\n');
		}
		files = files->next;
	}
}

static void	ft_del_list(t_list **head, char *path)
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
	free(path);
}

void		ft_print_list(t_list *files, t_ls ls_inf)
{
	if (files == NULL)
		return ;
	if ((ls_inf.opt >> SL_INDEX & 1) || (ls_inf.opt >> SO_INDEX & 1))
		ft_format_long(files, ls_inf);
	else
		ft_format_short(files, ls_inf);
}

void		ft_ls(char *path, t_ls ls_inf, int call)
{
	t_list	*files;
	t_list	*head;
	char	*name;

	errno = 0;
	if (call > 0 && ft_is_dir(path, NULL, 0))
		ft_printf("\n%s:\n", ft_strchr(path, '/') + 1);
	if ((files = ft_get_files(path)) != NULL)
	{
		ft_sort_by_options(&files, ls_inf.opt);
		head = files;
		ft_print_list(files, ls_inf);
		if (ls_inf.opt >> BR_INDEX & 1)
			while (files)
			{
				name = ft_strrchr(((t_file *)(files->content))->path, '/') + 1;
				if ((name[0] != '.' || (ls_inf.opt >> SA_INDEX & 1))
					&& ft_is_dir(path, files, 1))
					ft_ls(ft_get_next_path(path, files), ls_inf, call + 1);
				files = files->next;
			}
		ft_del_list(&head, path);
	}
}
