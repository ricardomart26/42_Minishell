/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:42:42 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/08 22:20:24 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @definition: Verifica se a arvore foi criada ou se e so 1 node com 1 comando
 * 
 * @params: node -> Contem o node da ABT
 *  
 * @return_value: Retorna verdade (1) se o lado direito e esquerdo forem iguais 
 * a NULL 
 * Retorna falso de a arvore tiver mais que um comando
 * 
 */

bool	is_empty_tree(t_node *node)
{
	if (node->l == NULL && node->r == NULL)
		return (true);
	return (false);
}
