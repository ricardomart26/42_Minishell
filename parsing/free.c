/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 21:58:36 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/16 14:30:40 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_one_node(t_node **node)
{
	int	i;

	i = -1;
	while (++i < (*node)->n_red)
		free((*node)->filename[i]);
	free((*node)->cmd);
	free((*node)->red);
	free(*node);
}

void	free_nodes(t_node **node)
{
	if (is_empty_tree(*node))
	{
		free_one_node(node);
		return ;
	}
	while ((*node)->r->type == PIPESS)
	{
		free_one_node(&(*node)->l);
		*node = (*node)->r;
	}
	free_one_node(&(*node)->l);
	free_one_node(&(*node)->r);
	free(*node);
}
