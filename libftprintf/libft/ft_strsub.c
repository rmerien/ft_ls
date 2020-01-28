/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 04:22:29 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/08 06:55:41 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *res;

	if (!s || !(res = (char *)malloc(len + 1)))
		return (NULL);
	ft_strncpy(res, s + start, len);
	res[len] = '\0';
	return (res);
}
