/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:42:06 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/25 22:48:25 by rimartin         ###   ########.fr       */
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

int	count_tokens(t_parser *parser, t_token find_token)
{
	int		i;
	int		counter;
	t_token	token;

	i = -1;
	counter = 0;
	while (parser->exp[++i])
	{
		parser->c = parser->exp[i];
		if (parser->exp[i + 1])
			parser->next_c = parser->exp[i + 1];
		else
			parser->next_c = 0;
		token = get_token(parser->c, parser->next_c);
		check_quotes(token, &parser->open_dq, &parser->open_q);
		if (token == find_token && (!parser->open_dq && !parser->open_q))
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

t_token	get_token(int c, int next_c)
{
	if (c == '|')
		return (PIPE);
	else if (c == ' ')
		return (SPACE);
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

t_token	get_token_with_c(int *c, int *next_c, char *str, int i)
{
	c_and_next(c, next_c, str, i);
	if (*c == '|')
		return (PIPE);
	else if (*c == ' ')
		return (SPACE);
	else if (*c == '"')
		return (DQ);
	else if (*c == '\'')
		return (Q);
	else if (*c == '<' && *next_c == '<')
		return (REDIRECTION);
	else if (*c == '>' && *next_c == '>')
		return (REDIRECTION);
	else if (*c == '<')
		return (REDIRECTION);
	else if (*c == '>')
		return (REDIRECTION);
	return (42);
}
