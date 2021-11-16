/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:15:43 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/16 19:41:47 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
int	if_builtin(char **line)
{
	fprintf(stderr, "teste\n");
	if (ft_strncmp(line[0], "cd", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "pwd", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "echo", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "exit", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "export", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "env", ft_strlen(line[0])) == 0)
		return (1);
	else if (ft_strncmp(line[0], "unset", ft_strlen(line[0])) == 0)
		return (1);
	fprintf(stderr, "teste 1\n");
	return (0);
}

void	heredoc_redirection_and_unlink_file(t_node *node)
{
	int	fd;
	int	i;

	fd = open(".temp_txt", O_RDONLY, 0777);
	dup2(fd, STDIN_FILENO);
	close(fd);
	i = -1;
	while (node->red[++i] != TO_HEREDOC)
		;
	if (unlink(node->filename[i]) == -1)
		perror("(heredoc_redirection_and_unlink_file) Error to destroy file in unlink");
}

int	free_no_void(void *str)
{
	free(str);
	return (1);
}

void	execute_cmd(t_node *node, char **env, t_parse *ps)
{
	char	**cmd;
	char	*cmd_path;
	char	**sp_path;

	check_redirections_on_command(node);
	sp_path = ft_split(get_env_path(env), ':');
	cmd = ft_split_quotes(ft_strtrim(node->cmd, " "));
	if (if_builtin(cmd))
		builtins(ps, &node, env, cmd);
	cmd_path = ft_str3join(*sp_path, "/", cmd[0]);
	while (access(cmd_path, F_OK) == -1 && *(sp_path++) != NULL
		&& free_no_void((void *)cmd_path))
		cmd_path = ft_str3join(*sp_path, "/", cmd[0]);
	if (!sp_path)
		error_msg("Not found command\n");
	if (node->has_heredoc)
		heredoc_redirection_and_unlink_file(node);
	execve(cmd_path, cmd, env);
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
	if_heredoc(node);
	while (++l.start <= l.end)
	{
		if (l.end != 0 && pipe(p) == -1)
			error_msg("Pipe error\n");
		else if (fork() == FORKED_CHILD)
		{
			if (l.end == 0)
				execute_cmd(node, env, ps);
			ft_handle_pipes(p, saved_p, l);
			if (l.start < l.end)
				execute_cmd(node->l, env, ps);
			else
				execute_cmd(node->r, env, ps);
		}
		else if (l.end != 0)
			saved_p = close_and_save_p(p, l, saved_p);
		else
		{
			wait(NULL);
			if (node->fd_h != -1)
				close(node->fd_h);
		}
		if (l.end != 0 && node->r->type != COMMAND)
			node = node->r;
	}
}
