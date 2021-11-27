/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 02:09:17 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/27 23:10:30 by rimartin         ###   ########.fr       */
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

void	get_red(t_node **curr, char *cmd, bool open_dq, bool open_q)
{
	int		pos;
	int		n_red;

	pos = -1;
	n_red = 0;
	malloc_guard((void **)&(*curr)->red, 1, sizeof(t_red));
	while (cmd[++pos])
	{
		check_quotes(get_token(cmd + pos), &open_dq, &open_q);
		if (get_token(cmd + pos) == REDIRECTION && (!open_dq && !open_q))
		{
			(*curr)->red[n_red++] = check_red(cmd + pos);
			(*curr)->red = realloc((*curr)->red, (n_red + 1) * sizeof(t_red));
			if ((*curr)->red[n_red - 1] == TO_HEREDOC
				|| (*curr)->red[n_red - 1] == TO_APPEND)
				pos++;
		}
	}
	(*curr)->red[n_red] = NOTHING;
	(*curr)->n_red = n_red;
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

void	parse_red(t_node **node)
{
	t_node	*curr;

	curr = *node;
	if (is_empty_tree(curr))
		get_red(&curr, curr->cmd, false, false);
	else
	{
		while (curr->r->end_of_tree != true)
		{
			get_red(&curr->l, curr->l->cmd, false, false);
			curr = curr->r;
		}
		get_red(&curr->l, curr->l->cmd, false, false);
		get_red(&curr->r, curr->r->cmd, false, false);
	}
}
