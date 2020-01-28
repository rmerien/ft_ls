/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magnitude.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:49:13 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/27 06:35:49 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_magnitude(long long int nb, int base)
{
	int res;

	res = 1 + (nb < 0);
	while (nb /= base)
		res++;
	return (res);
}

int	ft_unsigned_magnitude(unsigned long long int nb, int base)
{
	int res;

	res = 1;
	while (nb /= base)
		res++;
	return (res);
}
