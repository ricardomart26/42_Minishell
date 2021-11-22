/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:41:59 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/22 20:46:08 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_redirection_and_unlink_file(void)
{
	int	fd;

	fd = open(".temp.txt", O_RDWR, 0666);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	do_heredoc(t_node *node)
{
	int	i;

	i = 0;
	while (node->red[i] != NOTHING)
	{
		if (node->red[i] == TO_HEREDOC)
			rl_heredoc(node, ft_strtrim(node->filename[i], " "));
		i++;
	}
}

void	seek_for_heredoc(t_node *node)
{
	if (is_empty_tree(node))
	{
		if (node->n_red != 0)
			do_heredoc(node);
		return ;
	}
	while (node->r->type == IS_A_PIPE)
	{
		if (node->l->n_red != 0)
			do_heredoc(node->l);
		node = node->r;
	}
	if (node->l->n_red != 0)
		do_heredoc(node->l);
	if (node->r->n_red != 0)
		do_heredoc(node->r);
}

void	rl_heredoc(t_node *node, char *del)
{
	int		size_del;
	char	*exp;
	int		i;
	int		fd;

	if (!del)
		error_msg("Heredoc: Dont have delimiter\n");
	size_del = ft_strlen(del);
	i = 1;
	fd = open(".temp.txt", O_RDWR | O_CREAT, 0666);
	exp = readline("heredoc> ");
	while (1)
	{
		if (ft_strlen(exp) != 0 && !ft_strncmp(exp, del, ft_strlen(exp)))
			break ;
		write(fd, exp, ft_strlen(exp));
		write(fd, "\n", 1);
		exp = readline("heredoc> ");
	}
	close(fd);
	node->has_heredoc = true;
}
