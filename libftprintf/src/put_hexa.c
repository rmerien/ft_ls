/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hexa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:41:16 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/27 08:15:16 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	ft_pf_put_lhexa(va_list ap, t_pf_infos *inf)
{
	int				res;
	unsigned int	nb;

	nb = va_arg(ap, unsigned int);
	res = ft_pf_put_hexa_aux((unsigned long long int)nb, inf);
	return (res);
}

int	ft_pf_put_lhexa_l(va_list ap, t_pf_infos *inf)
{
	int					res;
	unsigned long int	nb;

	nb = va_arg(ap, unsigned long int);
	res = ft_pf_put_hexa_aux((unsigned long long int)nb, inf);
	return (res);
}

int	ft_pf_put_lhexa_ll(va_list ap, t_pf_infos *inf)
{
	int						res;
	unsigned long long int	nb;

	nb = va_arg(ap, unsigned long long int);
	res = ft_pf_put_hexa_aux(nb, inf);
	return (res);
}

int	ft_pf_put_lhexa_s(va_list ap, t_pf_infos *inf)
{
	int					res;
	unsigned short int	nb;

	nb = (unsigned short)va_arg(ap, int);
	res = ft_pf_put_hexa_aux((unsigned long long int)nb, inf);
	return (res);
}

int	ft_pf_put_lhexa_c(va_list ap, t_pf_infos *inf)
{
	int				res;
	unsigned char	nb;

	nb = (unsigned char)va_arg(ap, int);
	res = ft_pf_put_hexa_aux((unsigned long long int)nb, inf);
	return (res);
}
