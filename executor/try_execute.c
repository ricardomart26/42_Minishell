/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:03:27 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/06 00:09:56 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	exec_node(t_node *node, t_context *ctx, char **env);

int	exec_pipes(t_node *node, t_context *ctx, char **env)
{
	int			children;
	pid_t		p[2];
	t_context	ls_ctx;
	t_context	rs_ctx;

	if (pipe(p) == -1)
		fprintf(stderr, "(exec_pipes) Pipe of p[2] throw error\n");
	children = 0;
	ls_ctx = *ctx;
	fprintf(stderr, "ls first cmd %d\n", node->l->first_cmd);
	ls_ctx.fd[STDOUT_FILENO] = p[WRITE_END];
	ls_ctx.fd_close = p[READ_END];
	children += exec_node(node->l, &ls_ctx, env);
	rs_ctx = *ctx;
	rs_ctx.fd[STDIN_FILENO] = p[READ_END];
	rs_ctx.fd_close = p[WRITE_END];
	children += exec_node(node->r, &rs_ctx, env);
	close(p[READ_END]);
	close(p[WRITE_END]);
	return (children);
}

int	exec_command(t_node *node, t_context *ctx, char **env)
{
	char	**splited_path;
	char	*file_cmd;
	char	**cmd;

	splited_path = ft_split(get_env_path(env), ':');
	if (fork() == FORKED_CHILD)
	{
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		cmd = ft_split_quotes(ft_strtrim(node->cmd, " "), ' ');
		while (splited_path)
		{
			file_cmd = ft_str3join(*splited_path, "/", cmd[0]);
			splited_path++;
			if (access(file_cmd, F_OK) == -1)
				continue ;
			break ;
		}
		execve(file_cmd, cmd, env);
	}
	return (1);
}

int	exec_node(t_node *node, t_context *ctx, char **env)
{
	if (node->type == PIPESS)
		return (exec_pipes(node, ctx, env));
	else if (node->type == COMMAND)
		return (exec_command(node, ctx, env));
	else
		fprintf(stderr, "(exec_node) Type of node isn't right!\n");
	return (0);
}

void	tree_printer(t_node *node, int ident)
{
	int	i;

	i = -1;
	if (node->type == COMMAND)
	{
		while (++i < ident)
			write(1, " ", 1);
		fprintf(stderr, "COMMANDO: %s\n", ft_strtrim(node->cmd, " "));
	}
	else if (node->type == PIPESS)
	{
		while (++i < ident)
			write(1, " ", 1);
		fprintf(stderr, "PIPE:\n");
		tree_printer(node->l, ident + 4);
		tree_printer(node->r, ident + 4);
	}
}

void	exec(t_node *node, char **env)
{
	t_context	ctx;
	int			i;
	int			children;

	tree_printer(node, 0);
	ctx.fd[0] = STDIN_FILENO;
	ctx.fd[1] = STDOUT_FILENO;
	ctx.fd_close = -1;
	children = exec_node(node, &ctx, env);
	printf("children %d\n", children);
	i = -1;
	while (++i < children)
		wait(NULL);
}
