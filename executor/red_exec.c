/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 05:00:46 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/15 22:00:14 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_append(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND);
	if (fd == -1)
		error_msg("Error creating the file\n");
	if (access(filename, W_OK) == -1)
		perror("bash: Permission denied");
	dup2(fd, STDOUT_FILENO);
}

void	do_infile(char *filename)
{
	int	fd;
	
	if (access(filename, F_OK) == -1)
		perror("bash: No such file or directory");
	if (access(filename, R_OK) == -1)
		perror("bash: Permission denied");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_msg("Error creating a file\n");
	dup2(fd, STDIN_FILENO);
}

void	do_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC);
	fprintf(stderr, "file opened\n");
	if (fd == -1)
		error_msg("Error creating the file\n");
	if (access(filename, W_OK) == -1)
		perror("bash: Permission denied");
	dup2(fd, STDOUT_FILENO);
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
	fd = open(".temp_txt", O_CREAT | O_RDWR | O_TRUNC);
	node->fd_h = fd;
	exp = readline("heredoc> ");
	while (1)
	{
		if (!ft_strncmp(exp, del, ft_strlen(exp)))
			break ;
		write(fd, exp, ft_strlen(exp));
		write(fd, "\n", 1);
		exp = readline("heredoc> ");
	}
	// close(fd);
	// unlink fd
}
