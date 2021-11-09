/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 05:00:46 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/08 01:27:46 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*do_append(char *filename, int fd)
{
	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND);
	if (fd == -1)
		error_msg("Error creating the file\n");
	if (access(filename, W_OK) == -1)
		return ("bash: Permission denied");
	dup2(fd, STDOUT_FILENO);
	return (NULL);
}

char	*do_infile(char *filename, int fd)
{
	if (access(filename, F_OK) == -1)
		return ("bash: No such file or directory");
	if (access(filename, R_OK) == -1)
		return ("bash: Permission denied");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_msg("Error creating a file\n");
	dup2(fd, STDIN_FILENO);
	return (NULL);
}

char	*do_outfile(char *filename, int fd)
{
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd == -1)
		error_msg("Error creating the file\n");
	if (access(filename, W_OK) == -1)
		return ("bash: Permission denied");
	dup2(fd, STDOUT_FILENO);
	return (NULL);
}
