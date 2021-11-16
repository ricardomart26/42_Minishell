/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:21:48 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/16 12:12:47 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_dp(void **r, int fd, int len)
{
	int	i;

	i = -1;
	if (r == NULL)
		return ;
	if (len == 0)
	{
		while (r[++i])
			ft_putendl_fd(r[i], fd);
	}
	else
	{
		while (++i < len)
			ft_putstr_fd(r[i], fd);
	}
}
