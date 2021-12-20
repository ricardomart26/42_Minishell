/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:26:05 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/20 03:53:19 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_realloc(void *ptr, int new_size)
{
    void    *new_ptr;

    if (!ptr)
        return (malloc(new_size));
    new_ptr = malloc(new_size);
    printf("sizeof(ptr) %d new size %d\n", (int)sizeof(ptr), new_size);
    if (new_size > (int)sizeof(ptr))
        new_size = (int)sizeof(ptr);
    ft_memcpy(new_ptr, ptr, new_size);        
    free(ptr);
    return (new_ptr);
}