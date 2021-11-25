/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:49:57 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/25 22:55:09 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size(char *exp, int len_of_value, int len_of_var_in_dollar)
{
	int	size_to_alloc;

	size_to_alloc = ft_strlen(exp);
	if (len_of_value > len_of_var_in_dollar)
		size_to_alloc += (len_of_value - len_of_var_in_dollar);
	else if (len_of_value < len_of_var_in_dollar)
		size_to_alloc += len_of_var_in_dollar - len_of_value;
	return (size_to_alloc);
}

char	*replace_value(char *exp, char *value, t_vars_i_j v,
	int len)
{
	char		*temp;
	t_vars_i_j	l;
	int			save_i;

	temp = ft_strdup_and_free(&exp);
	exp = malloc(sizeof(char) * get_size(exp, ft_strlen(value), len) + 1);
	l.i = -1;
	l.j = 0;
	save_i = 0;
	while (temp[save_i])
	{
		l.i++;
		if (l.i == v.j)
		{
			l.j = 0;
			while (l.j < ft_strlen(value))
				exp[l.i++] = value[l.j++];
			l.j = len;
		}
		if (temp[save_i + l.j] == '\0')
			break ;
		exp[l.i] = temp[save_i++ + l.j];
	}
	exp[l.i] = '\0';
	return (exp);
}

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

char	*new_expand_vars(char *exp, t_lista *lst_env)
{
	t_vars_i_j	v;
	char		**split_exp;

	(void)lst_env;
	v.i = -1;
	split_exp = split_quotes(exp, 0);
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
		}
	}
	join_strings(&exp, split_exp);
	return (exp);
}
