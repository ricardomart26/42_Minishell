/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:49:57 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/29 22:16:12 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_for_value(char *var_name, t_lista *lst_value)
{
	t_lista	*curr;
	int		start;

	curr = lst_value;
	while (ft_strncmp(curr->content, var_name, ft_strlen(var_name))
		&& curr->next != NULL)
		curr = curr->next;
	if (!ft_strncmp(curr->content, var_name, ft_strlen(var_name)))
	{
		start = char_check(curr->content, '=');
		return (ft_substr(curr->content, start + 1,
				ft_strlen(curr->content)));
	}
	return (NULL);
}

void	get_variable_value(char **split_exp, t_lista *lst_value)
{
	char		*temp;
	char		*var_name;
	t_vars_i_j	v;
	char		*value_of_var;

	temp = ft_strdup(*split_exp);
	v.i = -1;
	v.j = 0;
	while (temp[++v.i])
	{
		if (v.i != 0 && temp[v.i - 1] == '$')
		{
			v.j = v.i - 1;
			while (!find_c_in_str(temp[v.i], SPACES) && temp[v.i] != '\0'
				&& temp[v.i] != '\'')
				v.i++;
			var_name = ft_substr(temp, v.j + 1, v.i - (v.j + 1));
			value_of_var = search_for_value(var_name, lst_value);
			if (value_of_var == NULL)
				perror("Didn't find variable in linked env");
			*split_exp = replace_value(*split_exp, value_of_var, v, v.i - v.j);
			if (temp[v.i] == '\0')
				break ;
		}
	}
}

void	join_strings(char **exp, char **split_exp)
{
	int		i;
	char	*temp;

	i = 0;
	free(*exp);
	*exp = split_exp[0];
	while (split_exp[++i])
	{
		temp = ft_str3join(*exp, " ", split_exp[i]);
		free(*exp);
		*exp = ft_strdup(temp);
		free(temp);
	}
}


// char	*get_home_var(t_lista *lst_env, char *path)
// {
// 	t_lista	*temp;

// 	temp = lst_env;
// 	while (ft_strncmp(temp->content, "HOME", 4) && temp != NULL)
// 		temp = temp->next;
// 	if (!ft_strncmp(temp->content, "HOME", 4))
// 	{
// 		if (path[1] && path[1] == '/')
// 			return (ft_strjoin(temp->content + 5, path + 1));
// 		return (temp->content + 5);
// 	}
// 	return (NULL);
// }


void	new_expand_vars(char **exp, t_lista *lst_env)
{
	t_vars_i_j	v;
	char		**split_exp;

	v.i = -1;
	split_exp = split_quotes(*exp, 0);
	while (split_exp[++v.i])
	{
		while (split_exp[v.i] != NULL && split_exp[v.i][0] == '\'')
			v.i++;
		if (split_exp[v.i] == NULL)
			break ;
		v.j = -1;
		while (split_exp[v.i][++v.j])
		{
			if (split_exp[v.i][v.j] == '$' && split_exp[v.i][v.j + 1] != '\0'
				&& split_exp[v.i][v.j + 1] != '?')
				get_variable_value(&split_exp[v.i], lst_env);
			if (v.j >= ft_strlen(split_exp[v.i]))
				break ;
		}
	}
	join_strings(exp, split_exp);
}
