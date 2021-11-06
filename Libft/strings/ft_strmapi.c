/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:40:58 by rimartin          #+#    #+#             */
/*   Updated: 2021/02/23 19:14:22 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	c;
	char			*str;
	int				size_str;

	if (!s || !f)
		return (NULL);
	size_str = ft_strlen((char *)s);
	str = (char *)malloc(size_str + 1);
	if (!str)
		return (NULL);
	c = 0;
	while (s[c])
	{
		str[c] = f(c, s[c]);
		c++;
	}
	str[c] = 0;
	return (str);
}
