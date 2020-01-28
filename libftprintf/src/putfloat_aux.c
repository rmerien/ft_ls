/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putfloat_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:04:27 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/30 23:53:29 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

char		*ft_pf_putfloat_get_addend_start(void)
{
	int		i;
	char	*res;

	if (!(res = ft_memalloc(65)))
		return (NULL);
	i = -1;
	while (++i < 64)
		res[i] = '0';
	res[1] = '5';
	return (res);
}

char		*ft_pf_putfloat_get_mantissa(int exponent)
{
	int		i;
	char	*res;

	if (!(res = ft_memalloc(65)))
		return (NULL);
	i = -1;
	while (++i < 64)
		res[i] = '0';
	if (exponent)
		res[0] = '1';
	return (res);
}

int			ft_pf_putfloat_count_dec(long double f)
{
	int res;

	if (f < 0.0)
		f *= -1.0L;
	if (f >= 1.0L || f == 0.0L)
		return (0);
	res = 1;
	while ((f *= 10.0L) < 1.0L)
		res++;
	return (res);
}

int			ft_pf_putfloat_show(char *result, short res_len, short man_len,
								t_pf_infos *inf)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	if (inf->is_x)
	{
		ret += (int)write(1, (inf->precision) == 0 ? "0" : "0.",
						(inf->precision) == 0 ? 1 : 2);
		while (--(inf->is_x) && (inf->precision)-- > 0)
			ret += (int)write(1, "0", 1);
		inf->is_x = 1;
	}
	while (i <= (int)(res_len - man_len - (inf->is_x ? 0 : 1)))
		if (!((inf->is_x > 0) && ((inf->precision)-- <= 0)))
			ret += (int)write(1, &(result[++i]), 1);
		else
			i++;
	if (!inf->is_x && (inf->precision > 0 || inf->sharp == 1))
		ret += (int)write(1, ".", 1);
	while ((inf->precision)-- > 0)
		ret += (int)write(1, &(result[++i]), 1);
	return (ret);
}

int			ft_float_pad(long double f, t_pf_infos *inf, int res_len,
				int man_len)
{
	int		bkp;
	int		reps;
	char	padder;

	bkp = 0;
	if (inf->justify == 2 || inf->zero == 1)
	{
		padder = (inf->zero-- == 1) ? '0' : ' ';
		if (f < 1.0L)
			reps = (inf->width) - (inf->bkp + 2)
						- (inf->space == 1 && f > 0.0L);
		else
			reps = (inf->width) - (inf->bkp + (res_len - man_len)
						+ (inf->space == 1 && f > 0.0L) + 2 + (inf->plus == 0));
		bkp = reps;
		while (reps-- > 0)
			write(1, &padder, 1);
	}
	else if (inf->space-- == 1 && f > 0.0L)
		bkp = (int)write(1, " ", 1);
	else if (inf->plus-- == 1 && f > 0.0L)
		bkp = (int)write(1, "+", 1);
	inf->justify++;
	return (ft_max(0, bkp));
}
