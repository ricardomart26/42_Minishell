/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 23:44:16 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/01 13:51:02 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_env_path(char **envp)
{
	int	x;

	x = 0;
	while (envp[x])
	{
		if (!ft_strncmp("PATH", envp[x], 4))
			return (envp[x] + 5);
		x++;
	}
	return (NULL);
}
