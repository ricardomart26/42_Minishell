/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:42:06 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/27 21:41:46 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @definition: Conta a quantidade de tokens na expressao recebida da readline
 * Example: Se o token for "\", entao o comando: ls -la | wc -l, vai contar como 
 * 1. 
 * 
 * @params: st -> Estrutura geral (So para nao ter que iniciar certas variaveis
 * em cada funcao, e para andar com a expressao recebida do readline pelas
 * funcoes)
 * st -> find_token vai ser o token que queremos contar
 *  
 * @return_value: Retorna o numero de tokens encontrado na expressao
 * 
 */

void	count_pipes(char *exp, int *n_pipes)
{
	int		i;
	bool	open_dq;
	bool	open_q;
	t_token	token;

	open_dq = false;
	open_q = false;
	i = -1;
	while (exp[++i])
	{
		token = get_token(exp + i);
		check_quotes(token, &open_dq, &open_q);
		if (token == PIPE && (!open_dq && !open_q))
			(*n_pipes)++;
	}
}

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
