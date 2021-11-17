/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:42:06 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/17 23:02:26 by rimartin         ###   ########.fr       */
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

int	count_tokens(t_others *others, t_token find_token)
{
	int		i;
	int		counter;
	t_token	token;

	i = -1;
	counter = 0;
	while (others->exp[++i])
	{
		others->c = others->exp[i];
		if (others->exp[i + 1])
			others->next = others->exp[i + 1];
		else
			others->next = 0;
		token = get_token(others->c, others->next);
		check_quotes(token, &others->open_dq, &others->open_q);
		if (token == find_token && (!others->open_dq && !others->open_q))
			counter++;
	}
	return (counter);
}

t_red	check_red(int c, int next)
{
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

t_token	get_token(int c, int next)
{
	if (c == '|')
		return (PIPE);
	else if (c == ' ')
		return (SPACE);
	else if (c == '"')
		return (DQ);
	else if (c == '\'')
		return (Q);
	else if (c == '<' && next == '<')
		return (REDIRECTION);
	else if (c == '>' && next == '>')
		return (REDIRECTION);
	else if (c == '<')
		return (REDIRECTION);
	else if (c == '>')
		return (REDIRECTION);
	return (42);
}
