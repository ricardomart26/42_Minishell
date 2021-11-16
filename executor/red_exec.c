/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 05:00:46 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/16 14:43:05 by rimartin         ###   ########.fr       */
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
				do_outfile(ft_strtrim(node->filename[i], " "));
		}
	}
}
