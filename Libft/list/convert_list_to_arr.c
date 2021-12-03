/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:00:09 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/03 00:00:25 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**convert_list_to_array(t_list *lista)
{
	char	**arr;
	int		i;

	arr = malloc((ft_lstsize((t_list *)lista) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	while (lista != NULL)
	{
		arr[++i] = ft_strdup(lista->content);
		lista = lista->next;
	}
	arr[i + 1] = NULL;
	return (arr);
}
