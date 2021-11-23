/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:08:18 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/23 19:13:21 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_unset(char *path, t_lista *lst)
{
	int		index;
	t_lista	*to_remove;
	t_lista	*curr;

	curr = lst;
	index = char_check(curr->content, '=');
	if (!ft_strncmp(curr->content, path, index) || (index == -1
			&& !ft_strncmp(curr->content, path, ft_strlen(path))))
	{
		to_remove = curr;
		curr = curr->next;
		free(to_remove);
		return (0);
	}
	return (1);
}

int	unset1(char *path, t_lista *lst)
{
	t_lista	*current;
	t_lista	*to_remove;
	int		index;

	index = 0;
	current = lst;
	if (first_unset(path, lst) == 0)
		return (0);
	while (current->next != NULL)
	{
		index = char_check(current->next->content, '=');
		if (!ft_strncmp(current->next->content, path, index) || (index == -1
				&& !ft_strncmp(current->next->content, path, ft_strlen(path))))
		{
			to_remove = current->next;
			current->next = current->next->next;
			free(to_remove);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	ft_unset(char *path, t_lista *lst_env, t_lista *lst_sort)
{
	t_lista	*current;
	t_lista	*to_remove;
	int		index;

	index = 0;
	current = lst_env;
	if (first_unset(path, lst_env) == 0)
		return (0);
	while (current->next != NULL)
	{
		index = char_check(current->next->content, '=');
		if (ft_strncmp(current->next->content, path, index) == 0)
		{
			to_remove = current->next;
			current->next = current->next->next;
			free(to_remove);
			unset1(path, lst_sort);
			return (0);
		}
		current = current->next;
	}
	if (unset1(path, lst_sort) == 0)
		return (0);
	return (1);
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
		g_error_code = COMMAND_NOT_FOUND;
	current = lst;
	while (current != NULL && !g_error_code)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}
