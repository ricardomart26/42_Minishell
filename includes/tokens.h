/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:41:55 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/27 21:00:57 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum s_token
{
	EMPTY,
	CHAR,
	PIPE,
	DQ,
	Q,
	ENV,
	REDIRECTION
}	t_token;

t_token	get_token(char *str);
// t_token	get_token(int c, int next);
void	current_char_and_next(int *c, int *next, char *str);

#endif
