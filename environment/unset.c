/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:08:18 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/02 23:44:58 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_unset(char *path, t_lista **lst)
{
	int		index;
	t_lista	*to_remove;

	index = char_check((*lst)->content, '=');
	if (!ft_strncmp((*lst)->content, path, index) || (index == -1
			&& !ft_strncmp((*lst)->content, path, ft_strlen(path))))
	{
		to_remove = *lst;
		*lst = (*lst)->next;
		free(to_remove);
		to_remove = NULL;
		return (0);
	}
	return (1);
}

t_lista	*unset1(char *path, t_lista *lst)
{
	t_lista	*current;
	t_lista	*to_remove;
	int		index;

	index = 0;
	current = lst;
	if (first_unset(path, &lst) == 0)
		return (lst);
	while (current->next != NULL)
	{
		index = char_check(current->next->content, '=');
		if ((ft_strlen(path) == index && !ft_strncmp(current->next->content,
					path, ft_strlen(path))) || (index == -1
				&& !ft_strncmp(current->next->content, path, ft_strlen(path))))
		{
			to_remove = current->next;
			current->next = current->next->next;
			free(to_remove);
			to_remove = NULL;
			return (lst);
		}
		current = current->next;
	}
	return (lst);
}

t_lista	*sub_unset(t_lista *current, t_listas *listas, char *path)
{
	int		index;
	t_lista	*to_remove;

	index = 0;
	if (current->next == NULL)
		return (listas->sort);
	index = char_check(current->next->content, '=');
	if ((ft_strlen(path) == index && !ft_strncmp(current->next->content,
				path, ft_strlen(path))) || (index == -1
			&& !ft_strncmp(current->next->content, path, ft_strlen(path))))
	{
		to_remove = current->next;
		current->next = current->next->next;
		free(to_remove);
		to_remove = NULL;
		listas->sort = unset1(path, listas->sort);
		return (listas->sort);
	}
	return (listas->sort);
}

t_listas	*ft_unset(char *path, t_listas *listas)
{
	t_lista	*current;

	current = listas->linked_env;
	if (first_unset(path, &listas->linked_env) == 0)
	{
		listas->sort = unset1(path, listas->sort);
		return (listas);
	}
	while (current != NULL)
	{
		listas->sort = sub_unset(current, listas, path);
		current = current->next;
	}
	unset1(path, listas->sort);
	return (listas);
}
