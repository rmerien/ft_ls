/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:46:31 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/09 02:12:31 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_putuint(va_list ap, t_pf_infos *inf)
{
	int				res;
	unsigned int	nb;

	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	nb = va_arg(ap, unsigned int);
	res = ft_pf_putullint_aux((unsigned long long int)nb, inf);
	return (res);
}

int	ft_pf_putulint(va_list ap, t_pf_infos *inf)
{
	int					res;
	unsigned long int	nb;

	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	nb = va_arg(ap, unsigned long int);
	res = ft_pf_putullint_aux((unsigned long long int)nb, inf);
	return (res);
}

int	ft_pf_putullint(va_list ap, t_pf_infos *inf)
{
	int						res;
	unsigned long long int	nb;

	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	nb = va_arg(ap, unsigned long long int);
	res = ft_pf_putullint_aux(nb, inf);
	return (res);
}

int	ft_pf_putusint(va_list ap, t_pf_infos *inf)
{
	int					res;
	unsigned short int	nb;

	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	nb = (unsigned short int)va_arg(ap, int);
	res = ft_pf_putullint_aux((unsigned long long int)nb, inf);
	return (res);
}

int	ft_pf_putucint(va_list ap, t_pf_infos *inf)
{
	int				res;
	unsigned char	nb;

	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	nb = (unsigned char)va_arg(ap, int);
	res = ft_pf_putullint_aux((unsigned long long int)nb, inf);
	return (res);
}
