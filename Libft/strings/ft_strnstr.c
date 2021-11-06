/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:38:45 by rimartin          #+#    #+#             */
/*   Updated: 2021/02/22 15:18:50 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	c;
	size_t	i;
	char	*ret;

	i = 0;
	ret = (char *)haystack;
	if (needle[i] == '\0')
		return (ret);
	while (ret[i] != '\0' && len > i)
	{
		c = 0;
		while (needle[c] == ret[i + c] && (i + c) < len)
		{
			if (needle[c + 1] == '\0')
				return (&ret[i]);
			c++;
		}
		i++;
	}
	return (NULL);
}
