/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 22:14:41 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/29 20:07:52 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	check_red(char *str)
{
	int	c;
	int	next;

	current_char_and_next(&c, &next, str);
	if (c == '<' && next == '<')
		return (TO_HEREDOC);
	else if (c == '>' && next == '>')
		return (TO_APPEND);
	else if (c == '<')
		return (TO_INFILE);
	else if (c == '>')
		return (TO_OUTFILE);
	return (NOTHING);
}

t_token	get_token(char *str)
{
	int	c;
	int	next_c;

	current_char_and_next(&c, &next_c, str);
	if (c == '|')
		return (PIPE);
	else if (c == '"')
		return (DQ);
	else if (c == '\'')
		return (Q);
	else if (c == '<' && next_c == '<')
		return (REDIRECTION);
	else if (c == '>' && next_c == '>')
		return (REDIRECTION);
	else if (c == '<')
		return (REDIRECTION);
	else if (c == '>')
		return (REDIRECTION);
	return (42);
}

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

/**
 * 
 * @definition: Recebe o caracter atual e o proximo (se existir)
 * 
 * @params: *c -> 
 * *next ->
 * *str ->
 * i ->
 *  
 * @return_value: (void)
 * 
 */

void	current_char_and_next(int *c, int *next, char *str)
{
	*c = str[0];
	*next = 0;
	if (str[1])
		*next = str[1];
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
