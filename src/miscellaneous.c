/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 06:57:42 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/11 05:04:41 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ft_printf.h"
#include "ft_ls.h"

#define C_DIR "\x1b[1;36m"
#define C_DIR_H "\x1b[30;43m"
#define C_EXE "\x1b[31m"
#define C_LINK "\x1b[35m"
#define C_RESET "\x1b[0m"

void	ft_colored_name(char *str, mode_t mode, int opt)
{
	if (opt >> SY_INDEX & 1)
	{
		ft_printf("%s", str);
		return ;
	}
	if (S_ISDIR(mode))
	{
		if (S_IRUSR & mode)
			ft_printf(C_DIR"%s"C_RESET, str);
		else
			ft_printf(C_DIR_H"%s"C_RESET, str);
	}
	else if (S_ISLNK(mode))
		ft_printf(C_LINK"%s"C_RESET, str);
	else if (S_IXUSR & mode)
		ft_printf(C_EXE"%s"C_RESET, str);
	else
		ft_printf("%s", str);
}
