/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:08:18 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/13 16:19:10 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	ft_unset(char *path, t_list **list_envp)
{
	t_list *to_remove;
	t_list *current;

	temp = NULL;
	if (ft_strncmp(path, list_envp->content, ft_strlen(path)) == 0)
	{
		temp = list_envp;
		list_envp = list_envp->next;
		ft_lstdelone(temp, free);
		return (0);
	}
	while (ft_strncmp(path, list_envp->content, ft_strlen(path)) != 0)
	{
		temp = list_envp;
		list_envp = list_envp->next;
	}
	temp->next = list_envp->next;
	ft_lstdelone(list_envp, free);
	return (0);
}*/

// void	ft_lstclear_env(t_lista **lst, void (*del)(void *))
// {
// 	t_lista	*current;

// 	while ((*lst)->next != NULL)
// 	{
// 		current = (*lst)->next;
// 		ft_lstdelone_env(*lst, del);
// 		*lst = current;
// 	}
// }

int ft_export(char *var, t_lista *envp, t_lista *sort)
{
	if (var == NULL)
		list_sort(sort);
	else
	{
		if (copy_check(var, sort, envp) == 0)
		{
			ft_lstadd_back((void *)&sort, ft_lstnew((void *)ft_strdup(var)));
			if (char_check(var, '=') != -1)
				ft_lstadd_back((void *)&envp, ft_lstnew((void *)ft_strdup(var)));
		}
	}
	return (0);
}

int	ft_env(t_lista *lst)
{
	t_lista *current;

	current = lst;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}
