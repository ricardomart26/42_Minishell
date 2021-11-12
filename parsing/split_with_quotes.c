/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:41:48 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/12 22:28:10 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_set_in_str(const char *set, char c)
{
	int i;

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

int	ft_cw(const char *s)
{
	int		i;
	bool	dq;
	bool	q;
	int		c;
	
	dq = false;
	q = false;
	i = -1;
	c = 0;
	while (s[++i])
	{
		while(s[i] == ' ')
			i++;
		while (find_quotes(s[i], &dq, &q) && s[i] != '\0')
		{
			while ((dq || q) && s[i] != '\0')
				find_quotes(s[++i], &dq, &q);
			while (s[i] != ' ' && s[i] != '\0')
				i++;
		}
		while (s[i] != ' ' && s[i] != '\0')
		{
			find_quotes(s[i], &dq, &q);
			while (dq || q)
				find_quotes(s[++i], &dq, &q);
			i++;
		}
		c++;
		if (s[i] == '\0')
			break ;
	}
	printf("cw: %d\n", c);
	return (c);
}

char	**collect(char const *s, int start, bool dq, bool q)
{
	int		size;
	int		k;
	char	**r;

	r = malloc(sizeof(char *) * ft_cw(s) + 1);
	q = false;
	dq = false;
	k = 0;
	while (s[start])
	{
		while (s[start] == ' ')
			start++;
		size = start;
		while (find_quotes(s[size], &dq, &q) && s[size] != '\0')
		{
			while (find_quotes(s[size], &dq, &q))
			{
				while ((dq || q) && s[size] != '\0')
					find_quotes(s[++size], &dq, &q);
				while (s[size] != ' ' && s[size] != '\0')
					size++;
			}
		}
		while (s[size] != ' ' && s[size] != '\0')
		{
			find_quotes(s[size], &dq, &q);
			while (dq || q)
				find_quotes(s[++size], &dq, &q);
			size++;
		}
		r[k++] = ft_substr(s, start, size - start);
		printf("collect r[%d] %s\n", k - 1, r[k - 1]);
		start = size;
	}
	r[k] = NULL;		
	return (r);
}

int	cl(char *str, bool dq, bool q)
{
	int		i;
	int		ret;
	
	i = -1;
	ret = 0;
	while (str[++i])
	{
		if (find_quotes(str[i], &dq, &q))
		{
			ret++;
			while (dq || q)
				find_quotes(str[i++], &dq, &q);
			ret++;		
		}
	}
	printf("cl: %d\n", ret);
	return (ret);
}

char	*magic_eraser_quotes(char *str, bool dq, bool q)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char *) * ft_strlen(str) - cl(str, dq, q) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	printf("str %s\n", str);
	while (*str)
	{
		if (find_quotes(*str, &dq, &q) && str++)
		{
			while ((dq || q) && *str)
			{
				ret[++i] = *(str++);
				find_quotes(*str, &dq, &q);
			}
			str++;
		}
		ret[++i] = *str;
		str++; 
	}
	ret[i + 1] = '\0';
	printf("ret %s i %d\n", ret, i);
	return (ret);
}

char **split_with_quotes(const char *s)
{
	int		i;
	int		x;
	char	**r;

	x = 0;
	r = collect(s, x, false, false);
	i = -1;
	while (r[++i])
		printf("split r[%d]: %s\n", i, r[i]);
	i = 0;
	while (r[i])
	{
		r[i] = magic_eraser_quotes(r[i], false, false);
		i++;
	}
	return (r);
}

int main(void)
{
	char **r;
	int		i;
	r = split_with_quotes("e\"ch\"o \"'-n'\"    lo \"   \"  teste");
	i = -1;
	while (r[++i])
		printf("r: %s\n", r[i]);
}
