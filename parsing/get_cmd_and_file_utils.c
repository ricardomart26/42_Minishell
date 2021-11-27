/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_and_file_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:21:18 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/27 22:51:54 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	command_doesnt_exist(char *cmd, t_node *curr)
{
	while (*cmd == ' ')
		cmd++;
	if (ft_strlen(cmd) == 0)
	{
		curr->cmd = NULL;
		return (true);
	}
	return (false);
}

void	file_or_cmd_in_front(t_node **c, t_vars_i_j v, char *cmd)
{
	if (v.i != 0)
		(*c)->filename = return_files((cmd + v.j), (*c)->n_red);
	else
		(*c)->cmd = ft_substr(cmd, 0, v.j);
}
