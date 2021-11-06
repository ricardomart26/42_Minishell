/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:36:55 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/31 19:58:28 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	norm_helper(t_split *sp, char const *s, int *i, int *counter)
{
	(*i)++;
	while (!check_quotes_split(s, &sp->dq, &sp->q, *i) && s[*i] != '\0')
		(*i)++;
	if (sp->dq == true || sp->q == true)
		return (-1);
	(*i)++;
	(*counter)++;
	return (0);
}

t_limit	norm_helper2(t_split *sp, char const *s, t_limit l, int *k)
{
	l.start = l.end + 1;
	l.end++;
	while (!check_quotes_split(s, &sp->dq, &sp->q, l.end) && s[l.end] != '\0')
		l.end++;
	if (sp->dq == true || sp->q == true)
		exit(5);
	sp->tab[(*k)++] = ft_strndup(s + l.start, l.end - l.start);
	l.end++;
	return (l);
}
