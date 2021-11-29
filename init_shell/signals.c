/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 05:58:23 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/29 22:02:34 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		printf("penis\n");
		if (g_gl.inside_command == 0)
		{
			rl_on_new_line();
			// rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			g_gl.error_code = 130;
	}
}
