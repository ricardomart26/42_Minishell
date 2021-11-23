/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:15:43 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/23 16:46:09 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_with_path(char *command_in_node, char **env)
{
	char	**only_command;
	char	*path;

	if (command_in_node[0] == '/')
	{
		only_command = split_quotes(ft_strrchr(command_in_node, '/') + 1, 0);
		path = ft_strndup(command_in_node, ft_strlen_c(command_in_node, ' '));
		if (execve(path, only_command, env) == -1)
			printf("bash: %s: command not found\n",
				eraser_quotes(command_in_node, false, false));
		return (1);
	}
	return (0);
}

void	execute_cmd(t_node *node, char **env, char *command_in_node)
{
	char	**cmd;
	char	*cmd_path;
	char	**sp_path;

	if (node->n_red != 0)
		check_redirections_on_command(node);
	if (node->has_heredoc)
		heredoc_redirection_and_unlink_file();
	if (!command_in_node)
		exit(4);
	if (is_command_with_path(command_in_node, env))
		;
	sp_path = ft_split(get_env_path(env), ':');
	cmd = split_quotes(command_in_node, 1);
	cmd_path = ft_str3join(*sp_path, "/", cmd[0]);
	while (access(cmd_path, F_OK) == -1 && *(sp_path++) != NULL
		&& free_with_return((void *)cmd_path))
		cmd_path = ft_str3join(*sp_path, "/", cmd[0]);
	if (execve(cmd_path, cmd, env) == -1)
		printf("bash: %s: command not found\n",
			eraser_quotes(node->cmd, false, false));
	exit(4);
}

void	child_exploration(t_node *node, t_pipes *p, int n_pipes, char **env)
{
	if (n_pipes == 0)
		execute_cmd(node, env, ft_strtrim(node->cmd, " "));
	handle_pipes(p->pfd, p->save_fd, p->index_for_pipes, n_pipes);
	if (p->index_for_pipes < n_pipes)
		execute_cmd(node->l, env, ft_strtrim(node->l->cmd, " "));
	else
		execute_cmd(node->r, env, ft_strtrim(node->r->cmd, " "));
}

void	ft_exec(t_node *node, int n_pipes, char **env)
{
	t_pipes	p;

	p.index_for_pipes = -1;
	seek_for_heredoc(node);
	if (is_empty_tree(node) && node->cmd == NULL)
		return ;
	while (++p.index_for_pipes <= n_pipes)
	{
		if (n_pipes != 0 && pipe(p.pfd) == -1)
			error_msg("Pipe error\n");
		else if (fork() == FORKED_CHILD)
			child_exploration(node, &p, n_pipes, env);
		else
			p.save_fd = close_and_save_p(&p, n_pipes);
		if (node->has_heredoc)
			unlink(".temp_txt");
		if (n_pipes != 0 && node->r->type != IS_A_COMMAND)
			node = node->r;
	}
}
