/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 04:36:14 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/11 03:27:48 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_print_usage(char c)
{
	write(2, "ft_ls: illegal option -- ", 25);
	write(2, &c, 1);
	write(2, "\nusage: ft_ls [-RSUalorty] [file ...]\n", 37);
	return (-1);
}

/*
** This function search for the character c in the string str
** and returns the index of c in str if it has been found or -1 otherwise
*/

static int	ft_c_index_in_str(char c, const char *str)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
		if (c == str[i])
			return (i);
	return (-1);
}

/*
** This function reads the arguments to find the options in it.
** It then returns the number of consumed arguments
*/

int			get_options(int argc, char **argv, int *result)
{
	int i;
	int j;
	int	index;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][0] != '-')
			break ;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] != '1')
				index = ft_c_index_in_str(argv[i][j], OPTIONS_STR);
			if (index == -1)
				return (ft_print_usage(argv[i][j]));
			*result |= 1 << index;
		}
	}
	return (i);
}
