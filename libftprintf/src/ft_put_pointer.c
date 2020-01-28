/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 08:17:20 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/30 21:43:39 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_hex(size_t nb)
{
	if (nb >= 16)
		ft_put_hex(nb / 16);
	ft_putchar((nb % 16) + ((nb % 16 >= 10) ? 'a' - 10 : '0'));
}

static int	ft_format_pointer(t_pf_infos *inf, int magnitude)
{
	int res;

	res = 0;
	if (inf->precision > -1 && inf->bkp == -10)
	{
		while ((inf->precision)-- - magnitude > -2)
			res += (int)write(1, "0", 1);
	}
	if (inf->width > -1 && inf->justify == -1 && inf->zero == -1)
	{
		while ((inf->width)-- - magnitude > 0)
			res += (int)write(1, " ", 1);
	}
	if (inf->zero == 1 && inf->bkp == -10)
	{
		while ((inf->width)-- - magnitude > 0)
			res += (int)write(1, "0", 1);
	}
	inf->bkp = -10;
	return (res);
}

static int	ft_justify(t_pf_infos *inf, int magnitude)
{
	int res;

	res = 0;
	while ((inf->width)-- - magnitude > 0)
		res += (int)write(1, " ", 1);
	return (res);
}

int			ft_put_pointer(va_list ap, t_pf_infos *inf)
{
	int		mag;
	int		res;
	size_t	ptr_value;
	size_t	bkp;

	ptr_value = (size_t)va_arg(ap, void *);
	mag = 2 + ((ptr_value == 0 && inf->precision == 0) ? 0
		: (ptr_value != 0 || (inf->precision == -1 || inf->width == -1)));
	bkp = ptr_value;
	while (bkp /= 16)
		mag++;
	res = mag;
	res += ft_format_pointer(inf, mag);
	ft_putstr("0x");
	res += ft_format_pointer(inf, mag);
	if (mag > 2)
		if ((ptr_value != 0 || (ptr_value == 0 && inf->precision != -1)
				|| inf->precision == -1))
			ft_put_hex(ptr_value);
	if (inf->justify > -1)
		res += ft_justify(inf, mag);
	return (res);
}
