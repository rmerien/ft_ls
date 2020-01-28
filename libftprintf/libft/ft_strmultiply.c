/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmultiply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 01:48:15 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/06 01:51:52 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short	ft_inputcheck(char *factor1, char *factor2)
{
	short i;
	short j;

	i = ft_strlen(factor1);
	j = ft_strlen(factor2);
	while (--i >= 0)
		if (!(ft_isdigit(factor1[i])))
			return (0);
	while (--j >= 0)
		if (!(ft_isdigit(factor2[j])))
			return (0);
	return (1);
}

static char		*ft_remove_trailing_zeros(char *result)
{
	char	*no_zeros;
	short	counter;

	counter = 0;
	while (result[counter] == '0' && result[counter + 1])
		counter++;
	no_zeros = ft_strdup(result + counter);
	free(result);
	return (no_zeros);
}

static char		*ft_initialize(size_t size)
{
	size_t	i;
	char	*new;

	i = -1;
	new = ft_strnew(size);
	while (++i < size)
		new[i] = '0';
	return (new);
}

char			*ft_strmultiply(char *factor1, char *factor2,
					short rm_front_zeros)
{
	short	i;
	short	j;
	short	rep;
	char	*result;
	int		add;

	if (!(ft_inputcheck(factor1, factor2)))
		return (ft_strcpy(ft_strnew(2), "0"));
	i = -1;
	rep = ft_strlen(factor1);
	result = ft_initialize(rep + ft_strlen(factor2));
	while (++i < rep)
	{
		add = 0;
		j = ft_strlen(factor2);
		while (--j >= 0)
		{
			add = (factor1[rep - 1 - i] - '0') * (factor2[j] - '0')
				+ (result[rep + j - i] - '0') + add;
			result[rep + j - i] = '0' + (add % 10);
			add /= 10;
		}
		result[rep + j - i] = ('0' + add);
	}
	return (rm_front_zeros ? ft_remove_trailing_zeros(result) : result);
}
