/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:02:41 by rimartin          #+#    #+#             */
/*   Updated: 2021/02/16 12:24:30 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		size;
	char	*ptr;

	size = 0;
	ptr = (char *)s;
	while (s[size])
		size++;
	if (c == '\0')
		return ((char *)s + size);
	while (0 < size--)
		if (ptr[size] == (char)c)
			return ((char *)s + size);
	return (0);
}
