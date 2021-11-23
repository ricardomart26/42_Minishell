/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:49:57 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/23 23:31:46 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_vars2(char *line, t_lista *current)
{
	int	start;

	start = 0;
	if (line[0] == '$' && line[1] != '?' && ft_strlen(line) != 1)
	{
		line = ft_substr(line, 1, ft_strlen(line) - 1);
		while (ft_strncmp(current->content, line, ft_strlen(line) != 0
				&& current->next != NULL))
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



// void	get_variable_value(char **new_split_exp, t_lista *lst_value)
// {
// 	char	*temp;
// 	char	*temp2;
// 	int		i;
// 	int		start;
// 	char	*var_value;

// 	temp = ft_strdup(*new_split_exp);
// 	free(*new_split_exp);
// 	i = -1;
// 	start = 0;
// 	while (temp[++i])
// 	{
// 		if (temp[i] == '$')
// 		{
// 			new_split_exp = ft_substr(temp, start, i - start);
// 			start = i;
// 			temp2 = find_
// 		}
// 	}
// }

// char	*new_expand_vars(char *exp, t_lista *lst_env)
// {
// 	t_vars_i_j	vars;
// 	char		**split_exp;
// 	char		*temp;

// 	(void)lst_env;
// 	vars.i = -1;
// 	split_exp = split_quotes(exp, 0);
// 	while (split_exp[++vars.i])
// 	{
// 		printf("split_exp %s\n", split_exp[vars.i]);
// 		while (split_exp[vars.i][0] == '\'' && split_exp[vars.i] != NULL)
// 			vars.i++;
// 		if (split_exp[vars.i] == NULL)
// 			break;
// 		vars.j = -1;
// 		while (split_exp[vars.i][++vars.j])
// 		{
// 			if (split_exp[vars.i][vars.j] == '$')
// 			{
// 				get_variable_value(&split_exp[vars.i], lst_env);
// 			}
// 		}
// 	}
// 	vars.i = 0;
// 	free(exp);
// 	exp = NULL;
// 	exp = split_exp[0];
// 	while (split_exp[++vars.i])
// 	{
// 		temp = ft_strjoin(exp, split_exp[vars.i]);
// 		exp = ft_strdup(temp);
// 		free(temp);
// 	}
// 	printf("resultado do temp no expand vars %s\n", temp);
// 	return (NULL);
// }