/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:28:24 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/28 04:51:13 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	rl_heredoc(char *del)
{
	int		size_del;
	char	*exp;
	int		i;
	int		fd;

	if (!del)
		error_msg("Heredoc: Dont have delimiter\n");
	size_del = ft_strlen(del);
	i = 1;
	fd = open("temp_txt", O_CREAT | O_WRONLY);
	exp = readline("heredoc> ");
	while (1)
	{
		write(fd, exp, ft_strlen(exp));
		exp = readline("heredoc> ");
		if (ft_strlen(exp) != 0 && !ft_strncmp(exp, del, ft_strlen(exp)))
			break ;
	}
	dup2(STDIN_FILENO, fd);
}
