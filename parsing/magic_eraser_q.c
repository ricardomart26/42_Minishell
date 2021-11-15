/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_eraser_q.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:01:59 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/15 17:51:41 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// printf("cl: %d\n", ret);
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
	// printf("str %s\n", str);
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
	// printf("ret %s i %d\n", ret, i);
	return (ret);
}
