/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:08:47 by rimartin          #+#    #+#             */
/*   Updated: 2021/02/25 18:26:08 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	temp = *lst;
	if (lst != NULL)
	{
		while (temp != NULL)
		{
			del((*lst)->content);
			temp = (*lst)->next;
			free(*lst);
		}
	}
	*lst = NULL;
}
