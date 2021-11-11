/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:15:43 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/11 20:39:41 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_node *node, char **env)
{
	char	**cmd;
	char	*file_cmd;
	char	**splited_path;

	splited_path = ft_split(get_env_path(env), ':');
	cmd = ft_split_quotes(ft_strtrim(node->cmd, " "), ' ');
	file_cmd = ft_str3join(*splited_path, "/", cmd[0]);
	while (access(file_cmd, F_OK) == -1 && *splited_path != NULL)
	{
		splited_path++;
		free(file_cmd);
		file_cmd = ft_str3join(*splited_path, "/", cmd[0]);
	}
	if (!splited_path)
		error_msg("Not found command\n");
	execve(file_cmd, cmd, env);
}

void	ft_handle_pipes(int p[2], int saved_p, t_limit l)
{
	if (l.start == 0)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
	}
	else if (l.start < l.end)
	{
		close(p[0]);
		dup2(saved_p, STDIN_FILENO);
		close(saved_p);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
	}
	else
	{
		close(p[1]);
		close(p[0]);
		dup2(saved_p, STDIN_FILENO);
		close(saved_p);
	}
}

int	close_and_save_p(int p[2], t_limit l, int saved_p)
{
	wait(NULL);
	if (l.start == 0)
	{
		saved_p = dup(p[0]);
		close(p[0]);
		close(p[1]);
	}
	else if (l.start < l.end)
	{
		close(saved_p);
		close(p[1]);
		saved_p = dup(p[0]);
		close(p[0]);
	}
	else
	{
		close(saved_p);
		close(p[0]);
		close(p[1]);
	}
	return (saved_p);
}

void	my_exec(t_node *node, t_parse *ps, char **env)
{
	int		p[2];
	t_limit	l;
	int		saved_p;

	l.start = -1;
	l.end = ps->n_pipes;
	while (++l.start <= l.end)
	{
		if (pipe(p) == -1)
			error_msg("Pipe error\n");
		if (fork() == FORKED_CHILD)
		{
			ft_handle_pipes(p, saved_p, l);
			if (l.start < l.end)
				execute_cmd(node->l, env);
			else
				execute_cmd(node->r, env);
		}
		else
			saved_p = close_and_save_p(p, l, saved_p);
		if (node->r->type != COMMAND)
			node = node->r;
	}
}
