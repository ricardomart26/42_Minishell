/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:14:54 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/18 04:54:54 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isalnum(const int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 'z') || (c >= '0' && c <= '9'))
		return (true);
	return (false);
}
