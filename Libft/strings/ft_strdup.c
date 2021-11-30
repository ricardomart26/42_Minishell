/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:41:32 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/30 21:33:57 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_dp(const char **s1)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * ft_strlen_dp(s1) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (s1[++i])
		ret[i] = ft_strdup(s1[i]);
	ret[i] = NULL;
	return (ret);
}

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

char	*ft_strdup_range(const char *s1, int st, int end)
{
	char	*dup;
	int		i;

	if (st == 0 && end == 0)
		return (ft_strdup(s1));
	dup = (char *)malloc(ft_strlen_range((char *)s1, st, end) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	if (end == 0)
	{
		while (s1[st] != '\0')
			dup[i++] = s1[st++];
	}
	if (i == 0)
	{
		while (st < end && s1[st] != '\0')
			dup[i++] = s1[st++];
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strdup_and_free(char **s1)
{
	char	*dup;

	dup = ft_strdup(*s1);
	free(*s1);
	s1 = NULL;
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
