/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 02:09:17 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/22 19:09:55 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @definition:
 * 
 * @params:
 *  
 * @return_value:
 * 
 */

t_red	*get_red(t_node *curr, t_parser *parser, char *cmd)
{
	int		pos;
	int		n_red;
	t_token	token;

	pos = -1;
	n_red = 0;
	malloc_guard((void **)&curr->red, 1, sizeof(t_red));
	while (cmd[++pos])
	{
		token = get_token_with_c(&parser->c, &parser->next_c, cmd, pos);
		check_quotes(token, &parser->open_dq, &parser->open_q);
		if (token == REDIRECTION && (!parser->open_dq && !parser->open_q))
		{
			curr->red[n_red++] = check_red(parser->c, parser->next_c);
			curr->red = realloc(curr->red, (n_red + 1) * sizeof(t_red));
			if (curr->red[n_red - 1] == TO_HEREDOC
				|| curr->red[n_red - 1] == TO_APPEND)
				pos++;
		}
	}
	curr->red[n_red] = NOTHING;
	curr->n_red = n_red;
	return (curr->red);
}

/**
 * 
 * @definition:
 * 
 * @params:
 *  
 * @return_value:
 * 
 */

void	parse_red(t_parser *parser, t_node **node)
{
	t_node	*curr;

	curr = *node;
	if (is_empty_tree(curr))
	{
		curr->red = get_red(curr, parser, curr->cmd);
		return ;
	}
	while (curr->r->end_of_tree != true)
	{
		curr->l->red = get_red(curr->l, parser, curr->l->cmd);
		curr = curr->r;
	}
	curr->l->red = get_red(curr->l, parser, curr->l->cmd);
	curr->r->red = get_red(curr->r, parser, curr->r->cmd);
}
