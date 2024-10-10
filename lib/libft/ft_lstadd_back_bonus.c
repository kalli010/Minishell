/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:25:01 by zelkalai          #+#    #+#             */
/*   Updated: 2023/11/19 00:12:08 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (lst == NULL || new == NULL)
		return (1);
	if (*lst == NULL)
	{
		*lst = new;
    return (0);
	}
	p = *lst;
	while (p->next != NULL)
		p = p->next;
  new->back = p;
  p->next = new;
  return(0);
}
