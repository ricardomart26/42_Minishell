/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:41:05 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/09 23:15:10 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	c;

	c = 0;
	while (str[c] != '\0')
		c++;
	return (c);
}

int	ft_strlen_range(const char *str, size_t st, size_t end)
{
	if (st + end >= ft_strlen(str))
		exit(1);
	if (st == 0 && end == 0)
		return (ft_strlen(str));
	if (end == 0)
	{
		while (str[st] != '\0')
			st++;
		return (st);
	}
	while (str[st] != '\0' && st <= end)
		st++;
	return (st);
}

int	ft_strlen_char(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;		
	return (i);
}
