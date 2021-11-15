/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:15:43 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/15 09:55:50 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
int	if_builtin(char **line)
{
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
	return (0);
}

void	check_redirections_on_command(t_node *node)
{
	int	i;

	i = -1;
	if (node->n_red != 0)
	{
		while (node->red[++i] != NOTHING)
		{
			printf("type of red on command %s: %d\n", node->cmd, node->red[i]);
			if (node->red[i] == TO_APPEND)
				do_append(ft_strtrim(node->filename[i], " "));
			else if (node->red[i] == TO_INFILE)
				do_infile(ft_strtrim(node->filename[i], " "));
			else if (node->red[i] == TO_OUTFILE)
			{
				fprintf(stderr, "Chegou aqui? 2\n");
				do_outfile(ft_strtrim(node->filename[i], " "));
			}
		}
	}
}


void	execute_cmd(t_node *node, char **env, t_parse *ps)
{
	char	**cmd;
	char	*file_cmd;
	char	**splited_path;

	check_redirections_on_command(node);
	fprintf(stderr, "Chegou aqui?\n");
	splited_path = ft_split(get_env_path(env), ':');
	cmd = ft_split_quotes(ft_strtrim(node->cmd, " "));
	if (if_builtin(cmd))
		builtins(ps, &node, env);
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

void	if_heredoc_do_heredoc(t_node *node)
{
	int	i;

	i = 0;
	while (node->red[i] != NOTHING)
	{
		if (node->red[i] == TO_HEREDOC)
		{
			rl_heredoc(ft_strtrim(node->filename[i], " "));
			break ;
		}
		i++;
	}
}


void	if_heredoc(t_node *node)
{
	if (is_empty_tree(node))
	{
		if (node->n_red != 0)
			if_heredoc_do_heredoc(node);
		return ;
	}
	while (node->r->type == PIPE)
	{
		if (node->l->n_red != 0)
			if_heredoc_do_heredoc(node->l);
		fprintf(stderr, "Weeeeeeee\n");
		node = node->r;
	}
	if (node->l->n_red != 0)
		if_heredoc_do_heredoc(node->l);
	if (node->r->n_red != 0)
		if_heredoc_do_heredoc(node->r);
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
		if (l.end != 0 && pipe(p) == -1)
			error_msg("Pipe error\n");
		else if (fork() == FORKED_CHILD)
		{
			if_heredoc(node);
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
			wait(NULL);
		if (l.end != 0 && node->r->type != COMMAND)
			node = node->r;
	}
}
