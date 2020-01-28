/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hexa_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:43:49 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/30 21:43:31 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

static int	ft_justify(t_pf_infos *inf)
{
	int		res;

	res = 0;
	while ((inf->width)-- > 0)
		res += (int)write(1, " ", 1);
	return (res);
}

static int	ft_handle_width(t_pf_infos *inf, int magnitude, int is_nul)
{
	int		res;
	char	pad;

	res = 0;
	pad = inf->zero == 1 ? '0' : ' ';
	inf->width -= (inf->space == 1) + 2 * (inf->sharp == 1) * !is_nul;
	if (inf->precision > -1 && inf->precision > magnitude)
		magnitude = ft_max(inf->precision + 1, magnitude);
	inf->width -= (inf->justify == 1 && inf->precision > -1)
						? inf->precision : 0;
	if (inf->justify == -1)
	{
		if (inf->zero == 1 && (inf->space == 1))
			res += (int)write(1, " ", 1);
		while ((inf->width)-- - magnitude > 0 - (inf->precision > magnitude
					|| (inf->precision == 0 && is_nul)))
			res += (int)write(1, &pad, 1);
	}
	else if (inf->precision == -1)
		inf->width -= magnitude;
	return (res);
}

static int	ft_format(t_pf_infos *inf, int magnitude, int is_nul)
{
	int		res;

	res = 0;
	if (inf->width > inf->precision && (inf->precision) > 0 && (inf->width) > 0)
		(inf->width) += (magnitude < inf->precision);
	if (inf->width > -1)
		res += ft_handle_width(inf, magnitude, is_nul);
	if (inf->space == 1)
		res += (int)write(1, " ", 1);
	if (inf->precision > 0)
		while ((inf->precision)-- - magnitude > 0 - is_nul)
			res += (int)write(1, "0", 1);
	return (res);
}

static void	ft_put_it(unsigned long long int nb, t_pf_infos *inf)
{
	if (nb >= 16)
		ft_put_it(nb / 16, inf);
	if (inf->is_x == 1)
		ft_putchar((nb % 16) + ((nb % 16 >= 10) ? 'a' - 10 : '0'));
	else
		ft_putchar((nb % 16) + ((nb % 16 >= 10) ? 'A' - 10 : '0'));
}

int			ft_pf_put_hexa_aux(unsigned long long int nb, t_pf_infos *inf)
{
	int res;
	int prec_zero;

	prec_zero = (inf->precision == 0);
	inf->precision -= (inf->precision > -1 && inf->sharp == 1);
	inf->bkp = inf->precision;
	res = (nb == 0 && prec_zero) ? 0 : ft_unsigned_magnitude(nb, 16);
	if (inf->zero == 1 && inf->sharp == 1 && inf->width == -1
		&& ((nb == 0 && !prec_zero) || nb != 0))
		res += (int)write(1, inf->is_x == 1 ? "0x" : "0X", 2);
	else if (!prec_zero && nb != 0 && inf->width == -1 && inf->justify == -1
		&& inf->sharp-- == 1 && inf->precision++)
		res += (int)write(1, inf->is_x == 1 ? "0x" : "0X", 2);
	else if (nb != 0 && inf->sharp == 1 && inf->zero == 1 && inf->width > -1)
		res += (int)write(1, inf->is_x == 1 ? "0x" : "0X", 2);
	res += ft_format(inf, ft_unsigned_magnitude(nb, 16), nb == 0);
	if ((inf->bkp != 0 && nb == 0) || (nb != 0))
	{
		if (inf->sharp == 1 && nb != 0 && inf->zero == -1)
			res += (int)write(1, inf->is_x == 1 ? "0x" : "0X", 2);
		if (!(prec_zero && nb == 0))
			ft_put_it(nb, inf);
	}
	res += (inf->justify == 1) ? ft_justify(inf) : 0;
	return (res);
}
