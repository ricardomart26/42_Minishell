/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:08:18 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/30 23:36:54 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_unset(char *path, t_lista *lst)
{
	int		index;
	t_lista	*to_remove;

	index = char_check(lst->content, '=');
	if (!ft_strncmp(lst->content, path, index) || (index == -1
			&& !ft_strncmp(lst->content, path, ft_strlen(path))))
	{
		printf("Removeu o primeiro?\n");
		to_remove = lst;
		lst = lst->next;
		free(to_remove);
		to_remove = NULL;
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
			to_remove = NULL;
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
	while (current != NULL)
	{
		index = char_check(current->content, '=');
		if (!ft_strncmp(current->content, path, index))
		{
			to_remove = current;
			current = current->next;
			printf("content %s\n", to_remove->content);
			free(to_remove->content);
			to_remove->content = NULL;
			free(to_remove);
			to_remove = NULL;
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
		g_gl.error_code = COMMAND_NOT_FOUND;
	current = lst;
	while (current != NULL && !g_gl.error_code)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}
