/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:40:53 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/21 22:51:11 by rimartin         ###   ########.fr       */
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

char	*check_if_redirection_first(t_parser *parser, char *cmd, t_node *node)
{
	t_token	token;
	int		i;
	int		size_until_next_space;

	// printf("See this one: cmd %s\n", cmd);
	token = get_token_with_c(&parser->c, &parser->next_c, cmd, 0);
	i = 0;
	while (token == REDIRECTION)
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
		token = get_token_with_c(&parser->c, &parser->next_c, cmd, 0);
	}
	if (i != 0)
		node->filename[i] = NULL;
	return (cmd);
}
