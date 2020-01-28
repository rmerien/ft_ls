/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:29:03 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/09 02:13:00 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format(t_pf_infos *inf, int length)
{
	int		res;
	char	padder;

	res = 0;
	if (inf->justify == -1)
	{
		padder = inf->zero == 1 ? '0' : ' ';
		while ((inf->width)-- - length > 0)
			res += (int)write(1, &padder, 1);
	}
	if (inf->bkp == -10)
	{
		while ((inf->width)-- - length > 0)
			res += (int)write(1, " ", 1);
	}
	inf->bkp = -10;
	return (res);
}

static int	ft_nulstr(t_pf_infos *inf)
{
	int		ret;
	char	pad;

	if (inf->precision == -1 && inf->width == -1)
		return ((int)write(1, "(null)", 6));
	ret = 0;
	pad = inf->zero == 1 ? '0' : ' ';
	while ((inf->width)-- > (inf->precision))
		ret += (int)write(1, &pad, 1);
	ret += (int)write(1, "(null)", ft_min(inf->precision, 6));
	return (ret);
}

int			ft_pf_putstr(va_list ap, t_pf_infos *inf)
{
	int			size;
	size_t		len;
	const char	*str;

	size = 0;
	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	str = va_arg(ap, const char *);
	if (str == NULL)
		return (ft_nulstr(inf));
	len = ft_strlen(str);
	len = inf->precision > -1 ? (size_t)ft_min(inf->precision, len) : len;
	size += ft_format(inf, len);
	size += (int)write(1, str, inf->precision == -1
				? len : (size_t)ft_min(inf->precision, len));
	size += ft_format(inf, len);
	return (size);
}
