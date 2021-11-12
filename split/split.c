/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:21:46 by ricardo          #+#    #+#             */
/*   Updated: 2021/11/11 23:41:45 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

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

int	ft_strlen(const char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

char    *ft_substr(char const *s, unsigned int i, size_t len)
{
    size_t    c;
    char    *temp;

    c = 0;
    if (!s)
        return (0);
    if (ft_strlen(s) < len)
        len = ft_strlen(s);
    temp = malloc(sizeof(s) * (len + 1));
    if (!temp)
        return (NULL);
    if (i >= ft_strlen(s))
    {
        temp[c] = '\0';
        return (temp);
    }
    while (c < len)
    {
        temp[c] = s[i];
        i++;
        c++;
    }
    temp[c] = '\0';
    return (temp);
}

char	**collect(char **r, char const *s, int start, int i)
{
	bool	q;
	bool	dq;
	int		size;
	int		k;
	
	q = false;
	dq = false;
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
				while (s[size] != ' ' && s[size] != s[size])
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
		start = size;
	}
	r[k] = NULL;		
	return (r);
}

int	ft_cw(const char *s)
{
	int		i;
	int		x;
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
			while (s[i] != ' ' && s[i] != s[i])
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
	printf("c: %d\n");
	return (c);
}

char **split(const char *s)
{
	int		i;
	int		x;
	int		k;
	char	**r;

	i = 0;
	x = 0;
	k = 0;
	r = malloc(sizeof(char *) * ft_cw(s));
	r = collect(r, s, x, i);
	return (r);
}

int main(void)
{
	char **r;
	int		i;
	r = split("echo \"'-n'\"    lo");
	i = -1;
	while (r[++i])
		printf("r: %s\n", r[i]);
}
