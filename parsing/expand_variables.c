/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:49:57 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/23 16:47:29 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_vars2(char *line, t_lista *current)
{
	int	start;

	start = 0;
	if (line[0] == '$' && ft_strlen(line) != 1)
	{
		line = ft_substr(line, 1, ft_strlen(line) - 1);
		while (ft_strncmp(current->content, line, ft_strlen(line) != 0
				&& current != NULL))
				current = current->next;
		if (ft_strncmp(current->content, line, ft_strlen(line)) == 0)
		{
			start = char_check(current->content, '=');
			line = ft_substr(current->content, start + 1,
					ft_strlen(current->content));
		}
	}
	return (line);
}

char	*expand_vars(char *line_var, t_lista *lst_envp)
{
	t_lista	*current;
	char	**line;
	int		index;

	index = 0;
	current = lst_envp;
	line = ft_split(line_var, ' ');
	while (line[index])
	{
		line[index] = expand_vars2(line[index], current);
		index++;
	}
	index = 1;
	while (line[index])
	{
		line[0] = ft_strjoin(line[0], ft_strjoin(" ", line[index]));
		index++;
	}
	return (line[0]);
}

// char	*new_expand_vars(char *exp, t_lista *lst_env)
// {
// 	t_vars_i_j	vars;
// 	char		**split_exp;

// 	(void)lst_env;
// 	vars.i = -1;
// 	split_exp = split_quotes(exp, 0);
// 	while (split_exp[++vars.i])
// 	{
// 		printf("split_exp %s\n", split_exp[vars.i]);
// 		vars.j = -1;
// 		while (split_exp[vars.i][++vars.j])
// 		{
// 			if (split_exp[vars.i][vars.j] == '$')
// 			{
// 			}
// 		}
// 	}
// 	return (NULL);
// }