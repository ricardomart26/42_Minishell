/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:34:44 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/30 22:41:28 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(char *error, char error_char)
{
	printf("%s", error);
	if (error_char)
		printf("%c\n", error_char);
	return (-1);
}

int	repeated_redirections(char **split_line, bool is_true)
{
	t_vars_i_j	vars;
	char		c;

	vars.i = -1;
	c = 0;
	while (split_line[++vars.i])
	{
		is_true = find_c_in_str(split_line[vars.i][0], "<>");
		if (is_true)
		{
			if (split_line[vars.i + 1] == NULL)
				return (error("syntax error near unexpected token ", c));
			c = split_line[vars.i + 1][0];
			is_true = find_c_in_str(c, "<>");
			if (is_true)
				return (error("syntax error near unexpected token ", c));
			if (split_line[vars.i][1] == '\0')
				continue ;
			c = split_line[vars.i][0];
			if ((split_line[vars.i][0] == '>' && split_line[vars.i][1] == '<')
			|| (split_line[vars.i][0] == '<' && split_line[vars.i][1] == '>'))
				return (error("syntax error near unexpected token ", c));
		}
	}
	return (0);
}

int	repeated_pipes(char **split_line)
{
	t_vars_i_j	vars;
	char		c;

	c = 0;
	if (split_line[0][0] == '|')
		return (error("syntax error near unexpected token ", '|'));
	vars.i = -1;
	while (split_line[++vars.i])
	{
		if (split_line[vars.i][0] == '|')
		{
			if (split_line[vars.i + 1] == NULL)
				return (error("syntax error near unexpected token ", '|'));
			c = split_line[vars.i + 1][0];
			if (c == '|')
				return (error("syntax error near unexpected token ", '|'));
			if (split_line[vars.i][1] == '\0')
				continue ;
			else if (split_line[vars.i][1] == '|')
				return (error("syntax error near unexpected token ", '|'));
		}
	}
	return (0);
}

int	not_valid_line(const char *line)
{
	char	**split_line;

	split_line = split_quotes(line, 0);
	if (repeated_pipes(split_line) && free_dp(split_line))
		return (258);
	else if (repeated_redirections(split_line, true) && free_dp(split_line))
		return (258);
	free_dp(split_line);
	return (0);
}
