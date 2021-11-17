/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:22:31 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/17 13:00:42 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;
	size_t			j;
	unsigned int	size;

	if (!s)
		return (NULL);
	size = (int)len;
	if (size >= ft_strlen((char *)s) - start)
		size = ft_strlen((char *)s) - start;
	if ((int)start >= ft_strlen((char *)s))
		size = 0;
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if ((i >= start && j < len))
			str[j++] = s[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}
