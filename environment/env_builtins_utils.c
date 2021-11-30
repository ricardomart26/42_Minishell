/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:11:14 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/30 15:57:10 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deallocate(t_lista **root)
{
	t_lista	*temp;
	t_lista	*current;

	current = *root;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free (temp);
	}
	*root = NULL;
}

void	list_init(t_listas **listas, char **env)
{
	int	index;

	index = 0;
	*listas = malloc(sizeof(t_listas));
	(*listas)->linked_env = (t_lista *)ft_lstnew(ft_strdup(env[index]));
	(*listas)->sort = (t_lista *)ft_lstnew(ft_strdup(env[index]));
	while (env[index + 1] != NULL)
	{
		ft_lstadd_back((void *)&(*listas)->linked_env,
			ft_lstnew((void *)ft_strdup(env[index + 1])));
		ft_lstadd_back((void *)&(*listas)->sort,
			ft_lstnew((void *)ft_strdup(env[index + 1])));
		index++;
	}
}

int	char_check(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

int	sub_copy_check(char *var, t_lista *current, t_lista *current1, int index)
{
	while (current != NULL)
	{
		if (ft_strncmp(var, current->content, index) == 0)
		{
			current->content = ft_strdup(var);
			current1->content = ft_strdup(var);
			return (-1);
		}
		current = current->next;
		current1 = current1->next;
	}
	return (0);
}

int	copy_check(char *var, t_lista *sort, t_lista *envp)
{
	int		index;
	t_lista	*current;
	t_lista	*current1;
	int		ret;

	ret = 0;
	current = sort;
	current1 = envp;
	index = char_check(var, '=');
	if (index == -1)
	{
		while (current != NULL)
		{
			if (!ft_strncmp(var, current->content, ft_strlen(current->content)))
				return (-1);
			current = current->next;
		}
	}
	else
	{
		ret = sub_copy_check(var, current, current1, index);
		if (ret == -1)
			return (-1);
	}
	return (0);
}
