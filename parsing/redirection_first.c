/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:40:53 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/27 21:04:58 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_rid_of_spaces(char **arg)
{
	while (is_space(**arg) && **arg != '\0')
		(*arg)++;
}

void	get_rid_of_set_and_spaces(char **arg, char *set)
{
	while ((find_c_in_str(**arg, set) || is_space(**arg)) && **arg != '\0')
		(*arg)++;
}

char	*if_file_first(char *cmd, t_node *node)
{
	int		i;
	int		size_until_next_space;

	i = 0;
	while (get_token(cmd) == REDIRECTION)
	{
		if (i == 0)
			node->filename = malloc(sizeof(char *) * 2);
		else
			node->filename = realloc(node->filename, sizeof(char *) * (i + 2));
		get_rid_of_set_and_spaces(&cmd, "<>");
		size_until_next_space = ft_strlen_c(cmd, ' ');
		node->filename[i++] = ft_substr(cmd, 0, size_until_next_space);
		cmd += size_until_next_space;
		get_rid_of_spaces(&cmd);
		if (*cmd == '\0')
			break ;
	}
	if (i != 0)
		node->filename[i] = NULL;
	return (cmd);
}
