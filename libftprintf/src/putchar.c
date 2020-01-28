/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:27:15 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/30 21:43:44 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format(t_pf_infos *inf)
{
	int		res;
	char	padder;

	res = 0;
	if (inf->justify == -1)
	{
		padder = inf->zero == 1 ? '0' : ' ';
		while ((inf->width)-- > 1)
			res += (int)write(1, &padder, 1);
	}
	if (inf->bkp == -10)
	{
		while ((inf->width)-- > 1)
			res += (int)write(1, " ", 1);
	}
	inf->bkp = -10;
	return (res);
}

int			ft_pf_putchar(va_list ap, t_pf_infos *inf)
{
	int				res;
	unsigned char	c;

	res = 0;
	res += ft_format(inf);
	c = (unsigned char)va_arg(ap, int);
	res += (int)write(1, &c, 1);
	res += ft_format(inf);
	return (res);
}
