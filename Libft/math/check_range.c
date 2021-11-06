/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 05:36:19 by ricardo           #+#    #+#             */
/*   Updated: 2021/09/19 04:52:09 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	range_int(int nbr, int min, int max)
{
	if (nbr >= min && nbr <= max)
		return (true);
	return (false);
}

bool	range_float(float nbr, float min, float max)
{
	if (nbr >= min && nbr <= max)
		return (true);
	return (false);
}

bool	range_double(double nbr, double min, double max)
{
	if (nbr >= min && nbr <= max)
		return (true);
	return (false);
}

bool	range_long(long nbr, long min, long max)
{
	if (nbr >= min && nbr <= max)
		return (true);
	return (false);
}

bool	range_biglong(long long nbr, long long min, long long max)
{
	if (nbr >= min && nbr <= max)
		return (true);
	return (false);
}
