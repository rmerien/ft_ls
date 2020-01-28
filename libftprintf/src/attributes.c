/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:27:03 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/05 17:48:32 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_pf_infos	*ft_pf_initiate_attributes(void)
{
	t_pf_infos *ret;

	if (!(ret = (t_pf_infos *)ft_memalloc(sizeof(t_pf_infos))))
		return (NULL);
	ret->space = -1;
	ret->justify = -1;
	ret->plus = -1;
	ret->precision = -1;
	ret->sharp = -1;
	ret->width = -1;
	ret->zero = -1;
	ret->is_x = -1;
	ret->is_b_x = -1;
	return (ret);
}

void		ft_pf_parse_attributes(t_pf_infos *inf, char conv)
{
	inf->conversion = conv;
	if (inf->zero > 0)
	{
		if (inf->precision > -1 && ft_pf_c_in_str(inf->conversion, "_diouxX"))
			inf->zero = -1;
		if (inf->justify == 1)
			inf->zero = -1;
	}
	if (inf->precision == -1)
		inf->precision = inf->conversion == 'f' ? 6 : -1;
	if (inf->plus == 1 && !ft_pf_c_in_str(inf->conversion, "_fdi"))
		inf->plus = -1;
	if (inf->plus == 1 && inf->space == 1)
		inf->space = -1;
	if (inf->space && !ft_pf_c_in_str(inf->conversion, "_di"))
		inf->space = -1;
}

void		ft_pf_get_attributes(t_pf_infos *inf, const char *str)
{
	inf->justify = (*str == '-') ? 1 : inf->justify;
	inf->zero = (*str == '0' && inf->precision == -1
						&& inf->width == -1) ? 1 : inf->zero;
	inf->sharp = (*str == '#') ? 1 : inf->sharp;
	inf->plus = (*str == '+') ? 1 : inf->plus;
	inf->space = (*str == ' ') ? 1 : inf->space;
	if (*str == '.')
		inf->precision = ft_atoi(str + 1);
	if (ft_isdigit(*str) && *str != '0' && inf->precision == -1
			&& inf->width == -1)
		inf->width = ft_atoi(str);
	if (*str == '*')
	{
		if (inf->precision == -1)
			inf->width = -42;
		else
			inf->precision = -42;
	}
}
