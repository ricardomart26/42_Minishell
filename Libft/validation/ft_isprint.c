/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:43:19 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/18 04:56:49 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	less_32(const int c)
{
	if (c >= 32)
		return (true);
	return (false);
}

static bool	bigger_126(const int c)
{
	if (c < 127)
		return (true);
	return (false);
}

bool	ft_isprint(const int c)
{
	if (less_32(c) && bigger_126(c))
		return (true);
	return (false);
}
