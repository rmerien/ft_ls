/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_conversions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 01:22:11 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/28 20:31:16 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_flag_offset(char c, int current_offset)
{
	if (c == 'l')
		return (10);
	else if (c == 'L')
		return (20);
	else if (c == 'h')
		return (current_offset >= 30 ? 10 : 30);
	return (0);
}

int	ft_pf_c_in_str(char c, char *str)
{
	int			i;

	i = -1;
	while (str[++i])
		if (c == str[i])
			return (i);
	return (0);
}

int	ft_conversion_or_flag(char c)
{
	return (c == 'f' || c == 'd' || c == 'i' || c == 'o' || c == 'u'
				|| c == 'x' || c == 'X' || c == 'h' || c == 'l' || c == 'L'
					|| c == 'c' || c == 's' || c == 'p');
}

int	ft_conversion(char c)
{
	return (c == 'f' || c == 'c' || c == 's' || c == 'd' || c == 'i'
				|| c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == 'p');
}
