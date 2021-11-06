/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:41:32 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/04 22:40:09 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int len)
{
	char	*dup;
	int		i;

	if (ft_strlen((char *)s1) <= len)
		return (ft_strdup(s1));
	dup = (char *)malloc(ft_strlen((char *)s1) + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < len)
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_strdup_and_free(char **s1)
{
	char	*dup;

	dup = ft_strdup(*s1);
	free(*s1);
	return (dup);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	dup = (char *)malloc(ft_strlen((char *)s1) + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (s1[++i])
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}
