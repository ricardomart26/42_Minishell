/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 02:09:17 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/17 22:59:06 by rimartin         ###   ########.fr       */
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

t_red	*get_red(t_node *curr, t_others *others, char *cmd)
{
	int		pos;
	int		n_red;
	t_token	token;

	pos = -1;
	n_red = 0;
	malloc_guard((void **)&curr->red, 1, sizeof(t_red));
	while (cmd[++pos])
	{
		c_and_next(&others->c, &others->next, cmd, pos);
		token = get_token(others->c, others->next);
		check_quotes(token, &others->open_dq, &others->open_q);
		if (token == REDIRECTION && (!others->open_dq && !others->open_q))
		{
			
			curr->red[n_red++] = check_red(others->c, others->next);
			printf("curr red %d\n", curr->red[n_red - 1]);
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

void	parse_red(t_others *others, t_node **node)
{
	t_node	*curr;

	curr = *node;
	if (is_empty_tree(curr))
	{
		curr->red = get_red(curr, others, curr->cmd);
		return ;
	}
	while (curr->r->end_of_tree != true)
	{
		curr->l->red = get_red(curr->l, others, curr->l->cmd);
		curr = curr->r;
	}
	curr->l->red = get_red(curr->l, others, curr->l->cmd);
	curr->r->red = get_red(curr->r, others, curr->r->cmd);
}
