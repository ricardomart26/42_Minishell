/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guards.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 22:40:17 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/04 22:40:22 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	malloc_guard(void **alloc_var, int size, int data_type_size)
{
	if (size <= 0 || data_type_size <= 0)
		error_msg("Error in malloc_guards: size or data size <= 0");
	*alloc_var = malloc(size * data_type_size);
	if (!(*alloc_var))
		error_msg("Error in malloc_guards: Couldn't alloc mem for variable");
}
