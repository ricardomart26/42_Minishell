/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:41:55 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/19 18:41:56 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum s_token
{
	EMPTY,
	CHAR,
	SPACE,
	PIPE,
	DQ,
	Q,
	ENV,
	REDIRECTION
}	t_token;

#endif