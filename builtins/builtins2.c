/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:44:41 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/30 19:40:58 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **line)
{
	if (!ft_strncmp(line[0], "cd", ft_strlen(line[0])) && free_dp(line))
		return (1);
	else if (!ft_strncmp(line[0], "pwd", ft_strlen(line[0])) && free_dp(line))
		return (1);
	else if (!ft_strncmp(line[0], "echo", ft_strlen(line[0])) && free_dp(line))
		return (1);
	else if (!ft_strncmp(line[0], "exit", ft_strlen(line[0])) && free_dp(line))
		return (1);
	else if (!ft_strncmp(line[0], "export", ft_strlen(line[0]))
		&& free_dp(line))
		return (1);
	else if (!ft_strncmp(line[0], "env", ft_strlen(line[0])) && free_dp(line))
		return (1);
	else if (!ft_strncmp(line[0], "unset", ft_strlen(line[0])) && free_dp(line))
		return (1);
	return (0);
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
			printf("%s\n", ft_substr(current->content, index,
					ft_strlen(current->content) - index));
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	sub_echo(char **line, t_listas *listas, int index)
{
	if (line[index][0] == '$' && line[index][1] != '?')
	{
		if (vars_echo(line[index], listas->linked_env) == 0)
			return (1);
	}
	else if (line[index][0] == '$' && index++)
	{
		printf("%d ", g_gl.error_code);
		g_gl.error_code = 0;
	}
	if (line[index])
		printf("%s", line[index]);
	else
		return (2);
	if (line[index + 1])
		printf(" ");
	return (0);
}

void	echo(char **line, int flag_n, t_listas *listas)
{
	int	index;
	int	ret;

	ret = 0;
	index = 1;
	if (flag_n == 1)
		index = 2;
	if (!line[index])
	{
		printf("\n");
		return ;
	}
	while (line[index])
	{
		ret = sub_echo(line, listas, index);
		if (ret == 1)
			return ;
		if (ret == 2)
			break ;
		index++;
	}
	if (flag_n == 0)
		printf("\n");
}
