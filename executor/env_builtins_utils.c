/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:11:14 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/20 19:46:48 by rimartin         ###   ########.fr       */
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
		ft_lstadd_back((void *)&(*listas)->linked_env, ft_lstnew((void *)ft_strdup(env[index + 1])));
		ft_lstadd_back((void *)&(*listas)->sort, ft_lstnew((void *)ft_strdup(env[index + 1])));
		index++;
	}
}

void	list_sort(t_lista *lst)
{
	t_lista	*current;
	t_lista	*after;
	char	*temp;
	int		index;

	index = 0;
	current = lst;
	while (current->next != NULL)
	{
		after = current->next;
		while (after != NULL)
		{
			index = 0;
			if ((unsigned char)current->content[0] > (unsigned char)after->content[0])
			{
				temp = ft_strdup(current->content);
				current->content = ft_strdup(after->content);
				after->content = ft_strdup(temp);
				free(temp);
			}
			else if ((unsigned char)current->content[0] == (unsigned char)after->content[0])
			{
				while ((unsigned char)current->content[index] == (unsigned char)after->content[index])
				{
					index++;
					if ((unsigned char)current->content[index] > (unsigned char)after->content[index])
					{
						temp = ft_strdup(current->content);
						current->content = ft_strdup(after->content);
						after->content = ft_strdup(temp);
					}
					else if ((unsigned char)current->content[index] < (unsigned char)after->content[index])
						break ;
				}
			}
			after = after->next;
		}
		printf("declare -x %s\n", current->content);
		current = current->next;
	}
	printf("declare -x %s\n", current->content);
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

int	copy_check(char *var, t_lista *sort, t_lista *envp)
{
	int		index;
	t_lista	*current;
	t_lista	*current1;

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
	}
	return (0);
}
