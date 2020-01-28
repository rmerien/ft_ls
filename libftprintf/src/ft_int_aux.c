/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:26:00 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/11 05:37:57 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_justify(t_pf_infos *inf, int is_neg)
{
	int		res;

	res = 0;
	while ((inf->width)-- > 0 + is_neg)
		res += (int)write(1, " ", 1);
	return (res);
}

static int	ft_handle_width(t_pf_infos *inf, int magnitude,
				int is_neg, int is_nul)
{
	int		res;
	char	pad;

	res = 0;
	pad = inf->zero == 1 ? '0' : ' ';
	if (is_neg && inf->zero == 1)
		write(1, "-", 1);
	inf->width -= (inf->plus == 1 || inf->space == 1);
	if (inf->precision > -1)
		magnitude = ft_max(inf->precision + 1, magnitude) + is_neg;
	inf->width -= (inf->justify == 1 && inf->precision > -1)
						? inf->precision : 0;
	if (inf->justify == -1)
	{
		if (inf->zero == 1 && ((inf->plus == 1 && !is_neg)
				|| inf->space == 1))
			res += (int)write(1, inf->plus == 1 ? "+" : " ", 1);
		while ((inf->width)-- - magnitude > 0 - (inf->precision > 0
					|| (inf->precision == 0 && is_nul)))
			res += (int)write(1, &pad, 1);
	}
	else if (inf->precision == -1)
		inf->width -= magnitude - is_neg;
	return (res);
}

static int	ft_format(t_pf_infos *inf, int magnitude, int is_neg, int is_nul)
{
	int		res;

	res = 0;
	if (inf->width > inf->precision && (inf->precision) > 0 && (inf->width) > 0
		&& magnitude > inf->precision && magnitude < inf->width && !is_neg)
		(inf->width)--;
	if (inf->width > -1)
		res += ft_handle_width(inf, magnitude, is_neg, is_nul);
	else if (is_neg && inf->zero == 1)
		write(1, "-", 1);
	if (inf->space == 1 && !is_neg && inf->zero == -1)
		res += (int)write(1, " ", 1);
	if (is_neg && inf->zero == -1)
		write(1, "-", 1);
	else if (inf->plus == 1 && inf->zero == -1 && !is_neg)
		res += (int)write(1, "+", 1);
	if (inf->precision > 0)
		while ((inf->precision)-- - magnitude > 0 - is_neg)
			res += (int)write(1, "0", 1);
	return (res);
}

static void	ft_put_it(long long nb)
{
	if (nb < 0)
	{
		if (nb == (-9223372036854775807 - 1))
		{
			write(1, "9223372036854775808", 19);
			return ;
		}
		else
			nb *= -1;
	}
	if (nb >= 10)
		ft_put_it(nb / 10);
	ft_putchar('0' + nb % 10);
}

int			ft_pf_putllint_aux(long long int nb, t_pf_infos *inf)
{
	int res;

	inf->bkp = inf->precision;
	if (inf->plus == 1 && nb < 0)
		inf->plus = -1;
	res = (nb == 0 && inf->precision == 0) ? 0 : ft_magnitude(nb, 10);
	res += ft_format(inf, ft_magnitude(nb, 10), nb < 0, nb == 0);
	if ((inf->bkp != 0 && nb == 0) || (nb != 0))
		ft_put_it(nb);
	if (inf->justify == 1)
		res += ft_justify(inf, nb < 0);
	return (res);
}
