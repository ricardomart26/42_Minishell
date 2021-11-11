/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:41:48 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/11 20:41:44 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_quotes_split(const char *str, bool *dq, bool *q, int i)
{
	if (str[i] == '"' && !(*q))
	{
		if (str[i - 1] != ' ' && *dq == false)
			*dq = true;
		else if (*dq == true)
			*dq = false;
		return (true);
	}
	else if (str[i] == '\'' && !(*dq))
	{
		if (str[i - 1] != ' ' && *q == false)
			*q = true;
		else if (*q == true)
			*q = false;
		return (true);
	}
	return (false);
}

void	init_vars(t_split *sp, int *a, int *b)
{
	sp->dq = false;
	sp->q = false;
	sp->tab = NULL;
	*a = 0;
	*b = 0;
}

static int	ft_cntwrd_quotes(char const *s, char c)
{
	int				i;
	int				counter;
	t_split			sp;

	if (!s)
		return (0);
	init_vars(&sp, &i, &counter);
	while (s[i])
	{
		while (s[i] == c && (s[i] != '\'' && s[i] != '"'))
			i++;
		if (check_quotes_split(s, &sp.dq, &sp.q, i))
		{
			if (norm_helper(&sp, s, &i, &counter) == -1)
				return (-1);
			if (s[i] == '\0')
				break ;
		}
		while (s[i] == c)
			i++;
		while (s[i] && ((s[i] != c) && (s[i] != '\'' && s[i] != '"')))
			i++;
		counter++;
	}
	return (counter + 1);
}

char	**ft_split_quotes(char const *s, char c)
{
	t_limit	l;
	int		k;
	t_split	sp;

	init_vars(&sp, &l.end, &k);
	sp.tab = malloc(sizeof(char *) * (ft_cntwrd_quotes(s, c) + 1));
	if (!sp.tab || !s)
		return (NULL);
	while (s[l.end])
	{
		while (s[l.end] == c)
			l.end++;
		l.start = l.end;
		if (check_quotes_split(s, &sp.dq, &sp.q, l.end))
		{
			l = norm_helper2(&sp, s, l, &k);
			continue ;
		}
		while (s[l.end] && s[l.end] != c)
			l.end++;
		if (l.end > l.start)
			sp.tab[k++] = ft_strndup(s + l.start, l.end - l.start);
	}
	sp.tab[k] = NULL;
	return (sp.tab);
}
