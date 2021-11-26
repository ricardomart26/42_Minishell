/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:19:56 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/26 00:01:02 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size(char *exp, int len_of_value, int len_of_var_in_dollar)
{
	int	size_to_alloc;

	size_to_alloc = ft_strlen(exp);
    printf("exp %s\n", exp);
	if (len_of_value > len_of_var_in_dollar) // 15 - 5
		size_to_alloc += (len_of_value - len_of_var_in_dollar);
	else if (len_of_value < len_of_var_in_dollar)
		size_to_alloc += len_of_var_in_dollar - len_of_value;
	return (size_to_alloc);
}

char	*replace_value
    (char *exp, char *value, t_vars_i_j v, int len)
{
	char		*temp;
	t_vars_i_j	l;
	int			save_i;

	temp = ft_strdup_and_free(&exp);
	exp = malloc(sizeof(char) * get_size(temp, ft_strlen(value), len) + 1);
	l.i = -1;
	l.j = 0;
	save_i = 0;
	while (temp[save_i])
	{
		l.i++;
		if (l.i == v.j)
		{
			l.j = 0;
			while (l.j < ft_strlen(value) && value[l.j] != '\0')
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
