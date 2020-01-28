/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 06:49:35 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/05 17:49:20 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		ft_pf_putint(va_list ap, t_pf_infos *inf)
{
	int	res;
	int	nb;

	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	nb = va_arg(ap, long int);
	res = ft_pf_putllint_aux((long long int)nb, inf);
	return (res);
}

int		ft_pf_putlint(va_list ap, t_pf_infos *inf)
{
	int			res;
	long int	nb;

	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	nb = va_arg(ap, long int);
	res = ft_pf_putllint_aux((long long int)nb, inf);
	return (res);
}

int		ft_pf_putllint(va_list ap, t_pf_infos *inf)
{
	int				res;
	long long int	nb;

	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	nb = va_arg(ap, long int);
	res = ft_pf_putllint_aux(nb, inf);
	return (res);
}

int		ft_pf_putsint(va_list ap, t_pf_infos *inf)
{
	int			res;
	short int	nb;

	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	nb = va_arg(ap, long int);
	res = ft_pf_putllint_aux((long long int)nb, inf);
	return (res);
}

int		ft_pf_putcint(va_list ap, t_pf_infos *inf)
{
	int		res;
	char	nb;

	if (inf->width == -42)
		inf->width = va_arg(ap, int);
	if (inf->precision == -42)
		inf->precision = va_arg(ap, int);
	nb = va_arg(ap, long int);
	res = ft_pf_putllint_aux((long long int)nb, inf);
	return (res);
}
