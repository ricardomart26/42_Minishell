/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:41:48 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/15 17:37:36 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_set_in_str(const char *set, char c)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (c == set[i])
			return (true);
	}
	return (false);
}

bool	find_quotes(char c, bool *dq, bool *q)
{
	if (c == '"' && !*q)
	{
		if (*dq == false)
			*dq = true;
		else if (*dq == true)
			*dq = false;
		return (true);
	}
	else if (c == '\'' && !*dq)
	{
		if (*q == false)
			*q = true;
		else if (*q == true)
			*q = false;
		return (true);
	}
	return (false);
}

int	inspect_while_quotes_or_spaces(char const *s, int i, bool dq, bool q)
{
	while (find_quotes(s[i], &dq, &q) && s[i])
	{
		while (find_quotes(s[i], &dq, &q))
		{
			while ((dq || q) && s[i])
				find_quotes(s[++i], &dq, &q);
			while (s[i] != ' ' && s[i])
				i++;
		}
	}
	while (s[i] != ' ' && s[i])
	{
		find_quotes(s[i], &dq, &q);
		while (dq || q)
			find_quotes(s[(++i)], &dq, &q);
		i++;
	}
	return (i);
}

int	ft_cw(const char *s, bool dq, bool q)
{
	int		i;
	int		c;

	i = -1;
	c = 0;
	while (s[++i])
	{
		while (s[i] == ' ')
			i++;
		i = inspect_while_quotes_or_spaces(s, i, dq, q);
		c++;
		if (s[i] == '\0')
			break ;
	}
	// printf("cw: %d\n", c);
	return (c);
}

char	**collect(char const *s, int start, bool dq, bool q)
{
	int		size;
	int		k;
	char	**r;

	r = malloc(sizeof(char *) * (ft_cw(s, false, false) + 1));
	k = 0;
	while (s[start])
	{
		while (s[start] == ' ')
			start++;
		size = start;
		size = inspect_while_quotes_or_spaces(s, size, dq, q);
		r[k++] = ft_substr(s, start, size - start);
		// printf("collect r[%d] %s\n", k - 1, r[k - 1]);
		start = size;
	}
	r[k] = NULL;
	return (r);
}

char	**ft_split_quotes(const char *s)
{
	int		i;
	int		x;
	char	**r;

	x = 0;
	r = collect(s, x, false, false);
	i = -1;
	while (r[++i])
		r[i] = magic_eraser_quotes(r[i], false, false);
	return (r);
}
