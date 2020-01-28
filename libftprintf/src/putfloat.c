/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putfloat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 01:04:16 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/30 23:56:20 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

static unsigned long long int	*ft_parse_float_bits(const void *float_mem)
{
	int								i;
	unsigned char					*mem;
	static unsigned long long int	s_e_m[3];

	i = -1;
	mem = (unsigned char *)float_mem;
	s_e_m[0] = (mem[9] & 128) ? 1 : 0;
	s_e_m[1] = ((mem[9] << 8) | (mem[8])) - ((1 << 15) * s_e_m[0]);
	s_e_m[2] = 0;
	while (++i < 8)
		s_e_m[2] |= ((unsigned long long int)(mem[i]) << (8 * i));
	if (s_e_m[0])
		ft_putchar('-');
	return (s_e_m);
}

static char						*ft_calculate_mantissa(
									unsigned long long int encoded_mantissa,
										int exponent)
{
	short	i;
	char	*mantissa;
	char	*addend;
	char	*to_free;

	i = 63;
	addend = ft_pf_putfloat_get_addend_start();
	mantissa = ft_pf_putfloat_get_mantissa(exponent);
	while (--i >= 0)
	{
		if (encoded_mantissa & (1ULL << i))
		{
			to_free = mantissa;
			mantissa = ft_stradd(addend, mantissa, 0);
			free(to_free);
		}
		to_free = addend;
		addend = ft_strmultiply(addend, "5", 0);
		addend[64] = '\0';
		free(to_free);
	}
	free(addend);
	return (ft_strmultiply(mantissa, "1", 1));
}

static char						*ft_calculate_exp(int exp_data)
{
	char	*exponent;

	if (exp_data == 16383)
		return (ft_strdup("1"));
	exponent = ft_strdup((exp_data - 16383 > 0) ? "2" : "5");
	return (ft_pf_binary_exponantiation(exponent,
					ft_itoa(ft_abs(exp_data - 16383))));
	return (exponent);
}

int								ft_print_result(long double f, char *result,
									t_pf_infos *inf, int man_len)
{
	int ret;
	int res_len;

	ret = 0;
	res_len = ft_strlen(result);
	inf->bkp = inf->precision;
	ret += ft_float_pad(f, inf, res_len, man_len);
	ret += ft_pf_putfloat_show(result, res_len, man_len, inf);
	if (inf->justify >= 1)
		ret += ft_float_pad(f, inf, res_len, man_len);
	return (ret);
}

int								ft_pf_putfloat(long double f, t_pf_infos *inf)
{
	unsigned long long int		*data;
	char						*result;
	char						*exponent;
	char						*mantissa;
	int							ret;

	if (f != 0.0L)
	{
		inf->is_x = ft_pf_putfloat_count_dec(f);
		inf->precision = (inf->precision == -1) ? 6 : inf->precision;
		data = ft_parse_float_bits((void *)&f);
		exponent = ft_calculate_exp((int)data[1]);
		mantissa = ft_calculate_mantissa(data[2], (int)data[1]);
		result = ft_strmultiply(exponent, mantissa, 1);
		ret = ft_print_result(f, result, inf, ft_strlen(mantissa)) + data[0];
		free(exponent);
		free(mantissa);
		free(result);
	}
	else
		ret = ft_print_result(f, "0", inf, 1);
	return (ret);
}
