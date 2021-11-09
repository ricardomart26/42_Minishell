/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 21:58:36 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/08 01:27:46 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_node(t_node **node)
{
	free((*node)->cmd);
	if ((*node)->n_red != 0)
	{
		while ((*node)->n_red-- != 0)
			free((*node)->filename[(*node)->n_red]);
		free((*node)->red);
	}
	free(*node);
	return (0);
}
