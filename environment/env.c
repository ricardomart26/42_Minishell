/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:58:47 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/02 20:21:41 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
