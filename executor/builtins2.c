/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:44:41 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/19 19:00:55 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **line)
{
	if (ft_strncmp(line[0], "cd", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "pwd", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "echo", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "exit", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "export", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "env", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "unset", ft_strlen(line[0])) == 0)
		return (1);
	return (0);
}

bool	is_builtin_out_of_child(t_node *node, int index_for_pipes, int n_pipes)
{
	if (index_for_pipes < n_pipes)
	{
		if (is_builtin(ft_split_quotes(node->cmd)))
			return (true);
	}
	else
	{
		if (is_builtin(ft_split_quotes(node->cmd)))
			return (true);
	}
	return (false);
}

int	vars_echo(char *line, t_lista *lst)
{
	int		index;
	t_lista	*current;

	index = 0;
	current = lst;
	while (current != NULL)
	{
		if (ft_strncmp(current->content, line, ft_strlen(line)) == 0)
		{
			index = char_check(current->content, '=');
			printf("%s\n", ft_substr(current->content, index, ft_strlen(current->content) - index));
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	echo(char **line, int flag_n, int error_code, t_listas *listas)
{
	int	index;

	index = 1;
	if (flag_n == 1)
		index = 2;
	while (line[index])
	{
		if (line[index][0] == '$')
		{
			if (line[index][1] != '?')
			{
				if (vars_echo(line[index], listas->linked_env) == 0)
					return (0);
			}
		}
		if (line[index + 1])
			printf(" ");
		index++;
	}
	if (flag_n == 0)
		printf("\n");
	return (error_code);
}
