/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 01:11:08 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/06 01:12:53 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_rotate_left(void *array, size_t array_size, size_t n,
			size_t data_size)
{
	size_t	i;
	void	*tmp;

	i = -1;
	n = n % (array_size / data_size);
	if (n == 0 || array_size / data_size == 1)
		return (array);
	if (!(tmp = ft_memalloc(data_size * n)))
		return (NULL);
	while (++i < n)
		ft_memcpy(tmp + (i * data_size), array + (i * data_size), data_size);
	i = -1;
	while (++i < (array_size / data_size) - n)
		ft_memcpy(array + (i * data_size), array + ((i + n) * data_size),
			data_size);
	i = -1;
	while (++i < n)
		ft_memcpy((array + array_size) - ((n - i) * data_size),
			tmp + (i * data_size), data_size);
	free(tmp);
	return (array);
}
