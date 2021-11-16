/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 02:09:17 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/16 14:28:12 by rimartin         ###   ########.fr       */
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

t_red	*get_red(t_node *curr, t_parse *st, char *cmd)
{
	int		pos;
	int		n_red;
	t_token	token;

	pos = -1;
	n_red = 0;
	malloc_guard((void **)&curr->red, 1, sizeof(t_red));
	while (cmd[++pos])
	{
		c_and_next(&st->c, &st->next, cmd, pos);
		token = get_token(st->c, st->next);
		check_quotes(token, &st->open_dq, &st->open_q);
		if (token == REDIRECTION && (!st->open_dq && !st->open_q))
		{
			curr->red[n_red++] = check_red(st->c, st->next);
			curr->red = realloc(curr->red, (n_red + 1) * sizeof(t_red));
			if (curr->red[n_red - 1] == TO_HEREDOC \
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

void	parse_red(t_parse *st, t_node **node)
{
	t_node	*curr;

	curr = *node;
	if (is_empty_tree(curr))
	{
		curr->red = get_red(curr, st, curr->cmd);
		return ;
	}
	while (curr->r->end_of_tree != true)
	{
		curr->l->red = get_red(curr->l, st, curr->l->cmd);
		curr = curr->r;
	}
	curr->l->red = get_red(curr->l, st, curr->l->cmd);
	curr->r->red = get_red(curr->r, st, curr->r->cmd);
}
