/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 21:17:27 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/28 22:00:38 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	set_brackets_to_true(char *line, int i, bool *brackets)
{
	if (line[i] == '{')
	{
		i++;
		*brackets = true;
	}
	return (i);
}

int	get_size_env(char *env, int pos)
{
	int	size;

	size = pos;
	while (ft_isalnum(env[pos]) && env[pos] != '\0')
		pos++;
	size = pos - size;
	return (size + 1);
}

static void	ft_lstdelone_env(t_env *lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst->keyword);
		del(lst->value);
		free(lst);
	}
}

void	ft_lstclear_env(t_env **lst, void (*del)(void *))
{
	t_env	*current;

	while ((*lst)->next != NULL)
	{
		current = (*lst)->next;
		ft_lstdelone_env(*lst, del);
		*lst = current;
	}
}