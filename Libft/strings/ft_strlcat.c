/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:41:18 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/18 04:26:49 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(const char *dst, const char *src, size_t size)
{
	char	*d;
	char	*s;
	size_t	len;
	size_t	dst_len;

	d = (char *)ft_memchr(dst, '\0', size);
	if (!d)
		return (size + ft_strlen((char *)src));
	s = (char *)src;
	d = (char *)dst;
	dst_len = ft_strlen(dst);
	len = dst_len + ft_strlen(s);
	d += dst_len;
	while (dst_len++ < size - 1 && *s)
		*d++ = *s++;
	*d = '\0';
	return (len);
}
