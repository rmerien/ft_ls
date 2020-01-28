/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 22:25:33 by rmerien           #+#    #+#             */
/*   Updated: 2018/12/11 03:23:57 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	ft_sort_ascii(t_list *list)
{
	t_list	*save;
	char	*a;
	char	*b;

	if (!list)
		return ;
	save = list;
	while (list && list->next)
	{
		a = ((t_file *)(list->content))->path;
		b = ((t_file *)(list->next->content))->path;
		if (ft_strcmp(a, b) > 0)
		{
			ft_swap(&list->content, &list->next->content);
			list = save;
		}
		else
			list = list->next;
	}
}

static inline void	ft_sort_time(t_list *list, int opt)
{
	t_list	*save;
	long	a;
	long	b;

	if (!list)
		return ;
	save = list;
	while (list && list->next)
	{
		a = (opt >> BU_INDEX & 1)
			? ((t_file *)(list->content))->infos.st_birthtimespec.tv_sec
			: ((t_file *)(list->content))->infos.st_mtimespec.tv_sec;
		b = (opt >> BU_INDEX & 1)
			? ((t_file *)(list->next->content))->infos.st_birthtimespec.tv_sec
			: ((t_file *)(list->next->content))->infos.st_mtimespec.tv_sec;
		if (b - a > 0)
		{
			ft_swap(&list->content, &list->next->content);
			list = save;
		}
		else
			list = list->next;
	}
}

static inline void	ft_sort_size(t_list *list)
{
	t_list	*save;
	int		a;
	int		b;

	if (!list)
		return ;
	save = list;
	while (list && list->next)
	{
		a = ((t_file *)(list->content))->infos.st_size;
		b = ((t_file *)(list->next->content))->infos.st_size;
		if (b - a > 0)
		{
			ft_swap(&list->content, &list->next->content);
			list = save;
		}
		else
			list = list->next;
	}
}

void				ft_sort_by_options(t_list **list, int options)
{
	ft_sort_ascii(*list);
	if (options >> BS_INDEX & 1)
		ft_sort_size(*list);
	else if (options >> ST_INDEX & 1)
		ft_sort_time(*list, options);
	if (options >> SR_INDEX & 1)
		ft_reverse_list(list);
}
