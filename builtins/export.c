/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:55:15 by jmendes           #+#    #+#             */
/*   Updated: 2021/11/08 01:57:33 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	int	c;

	c = 0;
	while (str[c] != '\0')
		c++;
	return (c);
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

/*
	O export tem que ser ordenado antes de imprimir
	O env tem é random
*/

int	main(int argc, char **argv, char **envp )
{
	int	index;

	index = 0;
	while (envp[index] != NULL)
	{
		printf("declare -x %s\n", envp[index]);
		index++;
	}
	if (argc == 2)
		envp[index] = ft_strdup(argv[1]);
	return (0);
}
