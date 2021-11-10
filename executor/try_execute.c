/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:55:07 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/10 21:39:40 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipes(t_node *node, t_context *ctx)
{
	int			children;
	pid_t		p[2];
	t_context	ls_ctx;
	t_context	rs_ctx;

	if (pipe(p) == -1)
		fprintf(stderr, "(exec_pipes) Pipe of p[2] throw error\n");
	children = 0;
	ls_ctx = *ctx;
	ls_ctx.fd[STDOUT_FILENO] = p[WRITE_END];
	ls_ctx.fd_close = p[READ_END];
	children += exec_node(node->l, &ls_ctx);
	rs_ctx = *ctx;
	rs_ctx.fd[STDIN_FILENO] = p[READ_END];
	rs_ctx.fd_close = p[WRITE_END];
	children += exec_node(node->r, &rs_ctx);
	close(p[READ_END]);
	close(p[WRITE_END]);
	return (children);
}

void	continue_exec(t_node *node, char **env)
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

int	exec_command(t_node *node, t_context *ctx)
{
	t_parse	*ps;
	t_env	*linked_env;
	int 	code;
	
	ps = singleton_ps(NULL);
	printf("env: %s\n", ps->env[0]);
	linked_env = singleton_env(NULL);
	if (fork() == FORKED_CHILD)
	{
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		code = builtins(ps, &linked_env, &node);
		if (code != 0)
			return (code);
		continue_exec(node, ps->env);
	}
	return (1);
}

int	exec_node(t_node *node, t_context *ctx)
{
	if (node->type == PIPESS)
		return (exec_pipes(node, ctx));
	else if (node->type == COMMAND)
		return (exec_command(node, ctx));
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
		fprintf(stderr, "PIPE: \n");
		tree_printer(node->l, ident + 4);
		tree_printer(node->r, ident + 4);
	}
}

void	exec(t_node *node)
{
	t_context	ctx;
	int			i;
	int			children;

	tree_printer(node, 0);
	ctx.fd[0] = STDIN_FILENO;
	ctx.fd[1] = STDOUT_FILENO;
	ctx.fd_close = -1;
	children = exec_node(node, &ctx);
	i = -1;
	while (++i < children)
		wait(NULL);
}
