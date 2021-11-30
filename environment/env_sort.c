/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:55:54 by jmendes           #+#    #+#             */
/*   Updated: 2021/11/30 23:19:09 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	under_sort(t_lista *after, t_lista *current, char *temp, int index)
{
	while ((unsigned char)current->content[index]
		== (unsigned char)after->content[index])
	{
		index++;
		if ((unsigned char)current->content[index]
			> (unsigned char)after->content[index])
		{
			temp = ft_strdup(current->content);
			current->content = ft_strdup(after->content);
			after->content = ft_strdup(temp);
		}
		else if ((unsigned char)current->content[index]
			< (unsigned char)after->content[index])
			break ;
	}
}

void	sub_sort(t_lista *after, t_lista *current)
{
	int		index;
	char	*temp;

	index = 0;
	temp = NULL;
	if ((unsigned char)current->content[0]
		> (unsigned char)after->content[0])
	{
		temp = ft_strdup(current->content);
		current->content = ft_strdup(after->content);
		after->content = ft_strdup(temp);
		free(temp);
		temp = NULL;
	}
	else if ((unsigned char)current->content[0]
		== (unsigned char)after->content[0])
		under_sort(after, current, temp, index);
}

void	list_sort(t_lista *lst)
{
	t_lista	*current;
	t_lista	*after;

	current = lst;
	while (current->next != NULL)
	{
		after = current->next;
		while (after != NULL)
		{
			sub_sort(after, current);
			after = after->next;
		}
		printf("declare -x %s\n", current->content);
		current = current->next;
	}
	printf("declare -x %s\n", current->content);
}
