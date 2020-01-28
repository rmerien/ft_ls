/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 04:39:02 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/11 05:38:51 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include "libft.h"

# define SL_INDEX 0
# define BR_INDEX 1
# define SA_INDEX 2
# define SR_INDEX 3
# define ST_INDEX 4
# define BS_INDEX 5
# define SO_INDEX 6
# define BU_INDEX 7
# define SY_INDEX 8
# define SIX_MONTHS 15780000

# define OPTIONS_STR "lRartSoUy"

/*
** Structure responsible of holding informations about a specific file
*/

typedef struct	s_max
{
	int			nl;
	int			pw;
	int			gr;
	int			size;
	int			total;
	int			is_dir;
}				t_max;

typedef struct	s_file
{
	char		*path;
	char		*short_path;
	struct stat	infos;
	int			valid;
}				t_file;

typedef struct	s_ls
{
	int			consumed;
	int			opt;
	int			argc;
	int			had_files;
	char		**argv;
}				t_ls;

/*
** Main and recursive function ft_ls :
*/

void			ft_ls(char *path_to_list, t_ls ls_inf, int call);

/*
** Long format printing (opt: the bitwise holder of the options)
*/

void			opt_l(t_file data, int opt, t_max vroum);
char			*ft_strmode(mode_t mode, char *path);

/*
** Functions annex to ft_ls
*/

void			ft_swap(void **a, void **b);
int				ft_is_dir(char *current_path, t_list *file, int check_point);
char			*ft_get_next_path(char *path_to_list, t_list *file);
char			*ft_append_str_slash(char *path_to_list, char *s2);
t_max			ft_fill_max(t_list *list, int opt);
int				ft_nblen(long long nb);
int				ft_is_symlink(char *path);
void			ft_print_list(t_list *files, t_ls ls_inf);

/*
** This function reads the arguments to find the options in it.
** It then returns the number of consumed arguments
*/

int				get_options(int argc, char **argv, int *result);

/*
** This function get all the files that are to be treated by the program
** and theb returns them into a list of structure
*/

t_list			*ft_get_files(char *path_to_list);
int				ft_add_file(t_list **result, char *path);
void			ft_reverse_list(t_list **list);

/*
** Sorting algorithms
*/

void			ft_sort_by_options(t_list **list, int options);

/*
** Colors (colors are ignored if -y option is passed)
*/

void			ft_colored_name(char *str, mode_t mode, int opt);

#endif
