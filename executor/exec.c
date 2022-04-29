/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:15:43 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/20 03:21:30 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_with_path(char *command_in_node, t_lista *env)
{
	char	**only_command;
	char	*path;

	if (command_in_node[0] == '/')
	{
		only_command = split_quotes(ft_strrchr(command_in_node, '/') + 1, 0);
		path = ft_strndup(command_in_node, ft_strlen_c(command_in_node, ' '));
		if (execve(path, only_command,
				convert_list_to_array((t_list *)env)) == -1)
			printf("bash: %s: command not found\n",
				eraser_quotes(command_in_node, false, false));
		exit(COMMAND_NOT_FOUND);
	}
	return (0);
}

char	*find_path_of_cmd(char **path, char *cmd)
{
	int		i;
	char	*get_path;

	i = -1;
	get_path = ft_str3join(path[++i], "/", cmd);
	while (get_path && access(get_path, F_OK) == -1
		&& free_with_return(get_path))
		get_path = ft_str3join(path[++i], "/", cmd);
	if (path[i] == NULL)
		return (NULL);
	return (get_path);
}

void	execute_cmd(t_node *node, t_lista *env, char *command_in_node)
{
	char	**cmd;
	char	**sp_path;
	char	*get_path;

	if (node->n_red != 0)
		check_redirections_on_command(node);
	if (node->has_heredoc)
		heredoc_redirection_and_unlink_file();
	if (!command_in_node)
		exit(4);
	if (is_command_with_path(command_in_node, env))
		;
	sp_path = ft_split(get_env_path(convert_list_to_array((t_list *)env)), ':');
	cmd = split_quotes(command_in_node, 1);
	if (sp_path)
		get_path = find_path_of_cmd(sp_path, cmd[0]);
	
	
	
	if (execve(get_path, cmd, convert_list_to_array((t_list *)env)) == -1)
		printf("bash: %s: command not found\n",
			eraser_quotes(node->cmd, false, false));
	exit(COMMAND_NOT_FOUND);
}

void	child_exploration(t_node *node, t_pipes *p, t_lista *env)
{
	if (p->n_pipes == 0)
		execute_cmd(node, env, ft_strtrim(node->cmd, " "));
	handle_pipes(p->pfd, p->save_fd, p->index_for_pipes, p->n_pipes);
	if (p->index_for_pipes < p->n_pipes)
		execute_cmd(node->l, env, ft_strtrim(node->l->cmd, " "));
	else
		execute_cmd(node->r, env, ft_strtrim(node->r->cmd, " "));
}

void	ft_exec(t_node *node, int n_pipes, t_lista *lista)
{
	t_pipes	p;

	g_gl.inside_command = 1;
	p.index_for_pipes = -1;
	p.n_pipes = n_pipes;
	seek_for_heredoc(node);
	if (is_empty_tree(node) && node->cmd == NULL)
	{
		if (node->has_heredoc)
			unlink(".temp_txt");
		return ;
	}
	if (pipe(p.pfd) == -1)
			error_msg("Pipe error\n");
	while (++p.index_for_pipes <= n_pipes)
	{
		g_gl.error_code = 0;
		if (pipe(p.pfd) == -1)
			error_msg("Pipe error\n");
		// if (n_pipes != 0)
		// 	error_msg("Pipe error\n");
		if (fork() == FORKED_CHILD)
			child_exploration(node, &p, lista);
		else
			p.save_fd = close_and_save_p(&p);
		if (node->has_heredoc)
			unlink(".temp_txt");
		if (p.n_pipes != 0 && node->r->type != IS_A_COMMAND)
			node = node->r;
	}
	g_gl.inside_command = 0;
}
