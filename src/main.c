/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 04:36:11 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/11 05:06:58 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "ft_printf.h"
#include "ft_ls.h"

static t_list	*ft_del_list(t_list **head)
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

static t_list	*ft_sort_args(int argc, char **argv, int cons, t_ls *ls_inf)
{
	t_list	*not_dir;
	t_list	*dir;

	if (argc == cons)
		ft_ls(ft_strdup("."), *ls_inf, 0);
	not_dir = NULL;
	dir = NULL;
	while (cons < argc)
	{
		errno = 0;
		if (!ft_is_dir(argv[cons], NULL, 1))
			ft_add_file(&not_dir, ft_strdup(argv[cons]));
		else
			ft_add_file(&dir,
				ft_strjoin((argv[cons][0] == '/') ? "" : "./", argv[cons]));
		cons++;
	}
	ls_inf->had_files = (not_dir != NULL);
	ft_sort_by_options(&not_dir, ls_inf->opt);
	ft_sort_by_options(&dir, ls_inf->opt);
	ft_print_list(not_dir, *ls_inf);
	ft_del_list(&not_dir);
	return (dir);
}

int				main(int argc, char **argv)
{
	int		call;
	int		cons;
	t_ls	ls_inf;
	t_list	*dir;
	t_list	*bkp;

	call = 0;
	ls_inf.opt = 0;
	ls_inf.had_files = 0;
	if ((cons = get_options(argc, argv, &(ls_inf.opt))) < 0)
		return (1);
	ls_inf.consumed = cons;
	ls_inf.argc = argc;
	ls_inf.argv = argv;
	dir = ft_sort_args(argc, argv, cons, &ls_inf);
	bkp = dir;
	while (dir)
	{
		ft_ls(ft_strdup(((t_file *)(dir->content))->path), ls_inf, call++
			+ ls_inf.had_files);
		dir = dir->next;
	}
	if (bkp)
		ft_del_list(&bkp);
	return (0);
}
