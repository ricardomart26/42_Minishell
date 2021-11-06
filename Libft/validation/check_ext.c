/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 23:43:57 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/04 22:28:30 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	check_ext(const char *file, const char *ext)
{
	int	size;
	int	size_ext;

	if (!ext && !file)
		return (false);
	size = ft_strlen(file) - 1;
	size_ext = ft_strlen(ext) - 1;
	file += size;
	ext += size_ext;
	while (*file == *ext && size_ext != 0)
	{
		file--;
		ext--;
		size_ext--;
	}
	if (size_ext == 0)
		return (true);
	return (false);
}
