/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 01:13:09 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/06 01:19:48 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	short	ft_inputcheck(char *addend1, char *addend2)
{
	short i;
	short j;

	i = ft_strlen(addend1);
	j = ft_strlen(addend2);
	while (--i >= 0)
		if (!(ft_isdigit(addend1[i])))
			return (0);
	while (--j >= 0)
		if (!(ft_isdigit(addend2[j])))
			return (0);
	return (1);
}

static	char	*ft_rm_trailing_zeros(char *result)
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

char			*ft_stradd(char *addend1, char *addend2, short rm_front_zeros)
{
	short	i;
	short	j;
	short	add;
	char	*result;

	if (!(ft_inputcheck(addend1, addend2)))
		return (ft_strcpy(ft_strnew(2), "0"));
	add = 0;
	i = ft_strlen(addend1);
	j = ft_strlen(addend2);
	result = ft_initialize(i + j);
	ft_strcpy(result + j, addend1);
	while (--j >= 0)
	{
		add = result[i + j] + addend2[j] - 2 * '0' + add;
		result[i + j] = '0' + (add % 10);
		add /= 10;
	}
	result[i + j] += add;
	return (rm_front_zeros ? ft_rm_trailing_zeros(result) : result);
}
