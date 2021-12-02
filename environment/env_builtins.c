/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:08:18 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/02 19:35:43 by jmendes          ###   ########.fr       */
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
		printf("Removeu o primeiro?\n");
	if (first_unset(path, &lst) == 0)
		return (lst);
	while (current->next != NULL)
	{
		index = char_check(current->next->content, '=');
		if (!ft_strncmp(current->next->content, path, ft_strlen(path)) || (index == -1
				&& !ft_strncmp(current->next->content, path, ft_strlen(path))))
		{
			to_remove = current->next;
			current->next = current->next->next;
		printf("Removeu o primeiro? %s\n", to_remove->content);
			free(to_remove);
			to_remove = NULL;
			return (lst);
		}
		current = current->next;
	}
	return (lst);
}

t_listas	*ft_unset(char *path, t_listas *listas)
{
	t_lista	*current;
	t_lista	*to_remove;
	int		index;

	index = 0;
	current = listas->linked_env;
	if (first_unset(path, &listas->linked_env) == 0)
	{
		listas->sort = unset1(path, listas->sort);
		return (listas);
	}
	while (current->next != NULL)
	{
		index = char_check(current->next->content, '=');
		if (!ft_strncmp(current->next->content, path, ft_strlen(path)) || (index == -1
				&& !ft_strncmp(current->next->content, path, ft_strlen(path))))
		{
			to_remove = current->next;
			current->next = current->next->next;
			free(to_remove);
			to_remove = NULL;
			listas->sort = unset1(path, listas->sort);
			return (0);
		}
		current = current->next;
	}
	if (unset1(path, listas->sort) == 0)
		return (listas);
	return (listas);
}

void	ft_export(char *var, t_lista *envp, t_lista *sort)
{
	if (var == NULL)
		list_sort(sort);
	else
	{
		if (copy_check(var, sort, envp) == 0)
		{
			ft_lstadd_back((void *)&sort, ft_lstnew((void *)ft_strdup(var)));
			if (char_check(var, '=') != -1)
				ft_lstadd_back((void *)&envp,
					ft_lstnew((void *)ft_strdup(var)));
		}
	}
}

void	ft_env(t_lista *lst, char *is_not_null)
{
	t_lista	*current;

	if (is_not_null)
		g_gl.error_code = COMMAND_NOT_FOUND;
	current = lst;
	while (current != NULL && !g_gl.error_code)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}
