/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:15:21 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/27 06:58:33 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		ft_pf_putoctal_ui(va_list ap, t_pf_infos *inf)
{
	int				res;
	unsigned int	nb;

	nb = va_arg(ap, unsigned int);
	res = ft_pf_putoctal_ulli_aux((unsigned long long int)nb, inf);
	return (res);
}

int		ft_pf_putoctal_uli(va_list ap, t_pf_infos *inf)
{
	int					res;
	unsigned long int	nb;

	nb = va_arg(ap, unsigned long int);
	res = ft_pf_putoctal_ulli_aux((unsigned long long int)nb, inf);
	return (res);
}

int		ft_pf_putoctal_ulli(va_list ap, t_pf_infos *inf)
{
	int						res;
	unsigned long long int	nb;

	nb = va_arg(ap, unsigned long long int);
	res = ft_pf_putoctal_ulli_aux(nb, inf);
	return (res);
}

int		ft_pf_putoctal_usi(va_list ap, t_pf_infos *inf)
{
	int					res;
	unsigned short int	nb;

	nb = (unsigned short)va_arg(ap, int);
	res = ft_pf_putoctal_ulli_aux((unsigned long long int)nb, inf);
	return (res);
}

int		ft_pf_putoctal_uci(va_list ap, t_pf_infos *inf)
{
	int				res;
	unsigned char	nb;

	nb = (unsigned char)va_arg(ap, int);
	res = ft_pf_putoctal_ulli_aux((unsigned long long int)nb, inf);
	return (res);
}
