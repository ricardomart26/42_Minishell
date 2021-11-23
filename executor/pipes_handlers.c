/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:52:00 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/23 19:38:08 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipes(int p[2], int save_fd, int index_for_pipes, int n_pipes)
{
	if (index_for_pipes == 0)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
	}
	else if (index_for_pipes < n_pipes)
	{
		close(p[0]);
		dup2(save_fd, STDIN_FILENO);
		close(save_fd);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
	}
	else
	{
		close(p[1]);
		close(p[0]);
		dup2(save_fd, STDIN_FILENO);
		close(save_fd);
	}
}

int	close_and_save_p(t_pipes *p, int n_pipes)
{
	waitpid(0, &g_error_code, 0);
	if (errno != 0)
		printf("%d\n", errno);
	if (n_pipes == 0)
		return (0);
	if (p->index_for_pipes == 0)
	{
		p->save_fd = dup(p->pfd[0]);
		close(p->pfd[0]);
		close(p->pfd[1]);
	}
	else if (p->index_for_pipes < n_pipes)
	{
		close(p->save_fd);
		close(p->pfd[1]);
		p->save_fd = dup(p->pfd[0]);
		close(p->pfd[0]);
	}
	else
	{
		close(p->save_fd);
		close(p->pfd[0]);
		close(p->pfd[1]);
	}
	return (p->save_fd);
}
