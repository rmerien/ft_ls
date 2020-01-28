/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 01:04:16 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/21 22:38:52 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MANTISSA_IMPLICIT_START "100000000000000000000000"
#define MANTISSA_EMPTY "000000000000000000000000"
#define MANTISSA_ADDEND_START "050000000000000000000000"
#define MIN_POWER_2 "00000000000000000000000000000000000000000000000000000002"
#define DENORMALIZED "5"

static int	*ft_parse_float_bits(const void *float_mem)
{
	static int		s_e_m[3];
	unsigned char	*mem;

	mem = (unsigned char *)float_mem;
	s_e_m[0] = (mem[3] & 128) ? 1 : 0;
	s_e_m[1] = ((mem[3] << 1) | (mem[2] >> 7 & 1)) - (256 * s_e_m[0]);
	s_e_m[2] = (mem[0] | (mem[1] << 8))
					| (((mem[2] - 128 * ((mem[2] >> 7) & 1)) << 16));
	if (s_e_m[0])
		ft_putchar('-');
	return (s_e_m);
}

static char	*ft_calculate_mantissa(int encoded_mantissa, int exponent)
{
	short	i;
	char	*mantissa;
	char	*addend;
	char	*to_free;

	i = 23;
	addend = malloc(25);
	mantissa = malloc(25);
	ft_strcpy(mantissa, exponent ? MANTISSA_IMPLICIT_START : MANTISSA_EMPTY);
	ft_strcpy(addend, MANTISSA_ADDEND_START);
	while (--i >= 0)
	{
		if (encoded_mantissa & (1 << i))
		{
			to_free = mantissa;
			mantissa = ft_stradd(addend, mantissa, 0);
			free(to_free);
		}
		to_free = addend;
		addend = ft_strmultiply(addend, "5", 0);
		addend[24] = '\0';
		free(to_free);
	}
	return (ft_strmultiply(mantissa, "1", 1));
}

static char	*ft_calculate_exp(int exp_data)
{
	short	i;
	char	*to_free;
	char	*exponent;

	i = 0;
	exponent = malloc(57);
	ft_strcpy(exponent, (exp_data - 127) >= 0 ? MIN_POWER_2 : DENORMALIZED);
	if ((exp_data - 127) >= 0)
		while (++i < exp_data - 127)
		{
			to_free = exponent;
			exponent = ft_strmultiply(exponent, "2", 0);
			free(to_free);
		}
	else
		while (--i > exp_data - 127)
		{
			to_free = exponent;
			exponent = ft_strmultiply(exponent, "5", 1);
			free(to_free);
		}
	return (exponent);
}

static void	ft_print_result(char *result, short res_len, short man_len)
{
	short	i;

	i = 0;
	while (i <= (short)(res_len - man_len))
		ft_putchar(result[i++]);
	if (i == 0)
		ft_putchar('0');
	ft_putchar('.');
	while (i <= (short)(res_len - man_len) + 6)
		ft_putchar(result[i++]);
}

void		ft_putfloat(float f)
{
	int			*data;
	char		*result;
	char		*exponent;
	char		*mantissa;

	data = ft_parse_float_bits((void *)&f);
	exponent = ft_calculate_exp(data[1]);
	mantissa = ft_calculate_mantissa(data[2], data[1]);
	result = ft_strmultiply(exponent, mantissa, 1);
	ft_print_result(result, ft_strlen(result),
		ft_strlen(mantissa) + ((data[1] - 127) < 0 ? ft_strlen(exponent) : 0));
	free(exponent);
	free(mantissa);
	free(result);
}
