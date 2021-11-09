/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 22:14:41 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/08 22:20:28 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	c_and_next(int *c, int *next, char *str, int i)
{
	*c = str[i];
	if (str[i + 1])
		*next = str[i + 1];
	else
		*next = 0;
}

/**
 * 
 * @definition: Procura um caracter dentro de uma string
 * 
 * @params: c -> Caracter a procurar
 * str -> String para procurar o caracter
 *  
 * @return_value: Retorna 1 se encontrar
 * Retorna 0 se nao encontrar
 * 
 */

bool	find_c_in_str(int c, char *str)
{
	while (*str)
	{
		if (c == *str)
			return (true);
		str++;
	}
	return (false);
}

/**
 * 
 * @definition: Verifica se encontrou uma double quote ou single quote, se 
 * encontrar verifica se ja estava aberta ou se e para abrir agora. Se a single
 * quote ja estiver "aberta" entao se encontrar uma double quote 
 * 
 * @params:
 *  
 * @return_value:
 * 
 */

bool	check_quotes(t_token token, bool *open_dq, bool *open_q)
{
	if (token == DQ && !(*open_q))
	{
		if (*open_dq == false)
			*open_dq = true;
		else if (*open_dq == true)
			*open_dq = false;
		return (true);
	}
	else if (token == Q && !(*open_dq))
	{			
		if (*open_q == false)
			*open_q = true;
		else if (*open_q == true)
			*open_q = false;
		return (true);
	}
	return (false);
}
