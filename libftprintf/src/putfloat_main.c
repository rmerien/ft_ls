/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putfloat_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 08:28:11 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/27 08:19:40 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_pf_is_greater_than_zero(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] != '0')
			return (1);
	return (0);
}

int			ft_pf_putfloat_f(va_list ap, t_pf_infos *inf)
{
	double f;

	f = va_arg(ap, double);
	return (ft_pf_putfloat((long double)f, inf));
}

int			ft_pf_putfloat_lf(va_list ap, t_pf_infos *inf)
{
	double f;

	f = va_arg(ap, double);
	return (ft_pf_putfloat((long double)f, inf));
}

int			ft_pf_putfloat_llf(va_list ap, t_pf_infos *inf)
{
	long double f;

	f = va_arg(ap, long double);
	return (ft_pf_putfloat(f, inf));
}

char		*ft_pf_binary_exponantiation(char *base, char *pow)
{
	char	*res;
	char	*tmp;

	res = ft_strdup("1");
	while (ft_pf_is_greater_than_zero(pow))
	{
		if (pow[ft_strlen(pow) - 1] % 2 == 1)
		{
			tmp = res;
			res = ft_strmultiply(res, base, 1);
			free(tmp);
		}
		tmp = base;
		base = ft_strmultiply(base, base, 1);
		free(tmp);
		pow = ft_strdivide_two(pow);
	}
	free(pow);
	free(base);
	return (res);
}
