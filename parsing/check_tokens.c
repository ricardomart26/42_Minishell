/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:42:06 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/08 22:15:40 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
