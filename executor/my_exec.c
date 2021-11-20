/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:15:43 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/20 12:28:40 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_no_void(void *str)
{
	free(str);
	return (1);
}

void	execute_cmd(t_node *node, char **env)
{
	char	**cmd;
	char	*cmd_path;
	char	**sp_path;

	check_redirections_on_command(node);
	sp_path = ft_split(get_env_path(env), ':');
	cmd = ft_split_quotes(ft_strtrim(node->cmd, " "));
	cmd_path = ft_str3join(*sp_path, "/", cmd[0]);
	while (access(cmd_path, F_OK) == -1 && *(sp_path++) != NULL
		&& free_no_void((void *)cmd_path))
		cmd_path = ft_str3join(*sp_path, "/", cmd[0]);
	if (node->has_heredoc)
		heredoc_redirection_and_unlink_file();
	if (node->cmd == NULL)
		exit(3);
	if (execve(cmd_path, cmd, env) == -1)
		printf("bash: %s: command not found\n", node->cmd);
}

void	ft_handle_pipes(int p[2], int save_fd, int index_for_pipes, int n_pipes)
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

int	close_and_save_p(int pfd[2], int index_for_pipes, int n_pipes, int save_fd)
{
	wait(NULL);
	if (index_for_pipes == 0)
	{
		save_fd = dup(pfd[0]);
		close(pfd[0]);
		close(pfd[1]);
	}
	else if (index_for_pipes < n_pipes)
	{
		close(save_fd);
		close(pfd[1]);
		save_fd = dup(pfd[0]);
		close(pfd[0]);
	}
	else
	{
		close(save_fd);
		close(pfd[0]);
		close(pfd[1]);
	}
	return (save_fd);
}

// save_stdin = dup(STDIN_FILENO)
// save_stdout = dup(STDOUT_FILENO)

void	my_exec(t_node *node, int n_pipes, char **env)
{
	int		pfd[2];
	int		save_fd;
	int		index_for_pipes;

	index_for_pipes = -1;
	seek_for_heredoc(node);
	if (is_empty_tree(node) && node->cmd == NULL)
		return ;
	while (++index_for_pipes <= n_pipes)
	{
		if (n_pipes != 0 && pipe(pfd) == -1)
			error_msg("Pipe error\n");
		else if (fork() == FORKED_CHILD)
		{
			if (n_pipes == 0)
				execute_cmd(node, env);
			ft_handle_pipes(pfd, save_fd, index_for_pipes, n_pipes);
			if (index_for_pipes < n_pipes)
				execute_cmd(node->l, env);
			else
				execute_cmd(node->r, env);
		}
		else if (n_pipes != 0)
			save_fd = close_and_save_p(pfd, index_for_pipes, n_pipes, save_fd);
		else
			wait(NULL);
		if (node->has_heredoc)
			unlink(".temp_txt");
		if (n_pipes != 0 && node->r->type != COMMAND)
			node = node->r;
	}
}
