/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_eraser_q.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:01:59 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/22 19:33:36 by rimartin         ###   ########.fr       */
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
			while ((dq || q) && str[i] != '\0')
			{
				find_quotes(str[i + 1], &dq, &q);
				i++;
			}
			ret++;
		}
		if (str[i] == '\0')
			break ;
	}
	return (ret);
}

char	*eraser_quotes(char *str, bool dq, bool q)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char *) * ft_strlen(str) - cl(str, dq, q) + 1);
	if (!ret)
		return (NULL);
	i = -1;
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
		if (*str == '\0')
			break ;
		str++;
	}
	ret[i + 1] = '\0';
	return (ret);
}
