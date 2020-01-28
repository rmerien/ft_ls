/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 22:27:05 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/09 01:27:16 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Reverses a list :)
** (Captain Obvious)
*/

void	ft_reverse_list(t_list **head)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*next;

	prev = NULL;
	curr = *head;
	next = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}
