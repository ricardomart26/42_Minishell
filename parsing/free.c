/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 21:58:36 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/30 21:41:15 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_dp(char **dp)
{
	int	x;

	x = -1;
	while (dp[++x])
	{
		free(dp[x]);
		dp[x] = NULL;
	}
	free(dp);
	dp = NULL;
	return (1);
}

int	free_with_return(void *str)
{
	free(str);
	str = NULL;
	return (1);
}

void	free_one_node(t_node *node)
{
	int	i;

	i = -1;
	while (++i < node->n_red)
	{
		free(node->filename[i]);
		node->filename[i] = NULL;
	}
	free(node->cmd);
	node->cmd = NULL;
	free(node->red);
	node->red = NULL;
	free(node);
	node = NULL;
}

void	free_nodes(t_node *node, char **exp)
{
	t_node *temp;

	temp = node;
	g_gl.n_pipes = 0;
	free(*exp);
	*exp = NULL;
	if (is_empty_tree(node))
		free_one_node(node);
	else
	{
		while (node->r->type == IS_A_PIPE)
		{
			free_one_node(node->l);
			node = node->r;
		}
		free_one_node(node->l);
		free_one_node(node->r);
		free(temp);
		temp = NULL;
	}
}
