/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:05:27 by jmendes           #+#    #+#             */
/*   Updated: 2021/11/26 01:50:18 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	path[1040];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
		g_error_code = GENERAL_ERROR;
}

void	cd(char *path)
{
	if (chdir(path) != 0)
	{
		printf("ERROR: NO DIRECTORY");
		g_error_code = GENERAL_ERROR;
	}
}

void	exit_builtin(t_parser *parser, t_lista *env, t_lista *sort, t_node **node)
{
	ft_lstclear((t_list **)&sort, free);
	ft_lstclear((t_list **)&env, free);
	free_nodes(node, parser);
	exit(0);
}

int	builtins(t_parser *parser, t_node **node, t_listas *listas, char **line)
{
	int			echo_n;

	echo_n = 0;
	if (!ft_strncmp(line[0], "cd", ft_strlen(line[0])))
		cd(line[1]);
	else if (!ft_strncmp(line[0], "pwd", ft_strlen(line[0])))
		pwd();
	else if (!ft_strncmp(line[0], "echo", ft_strlen(line[0])))
	{
		if (!ft_strncmp(line[1], "-n", ft_strlen(line[1])))
			echo_n = 1;
		echo(line, echo_n, listas);
	}
	if (!ft_strncmp(line[0], "exit", ft_strlen(line[0])))
		exit_builtin(parser, listas->linked_env, listas->sort, node);
	if (!ft_strncmp(line[0], "export", ft_strlen(line[0])))
		ft_export(line[1], listas->linked_env, listas->sort);
	if (!ft_strncmp(line[0], "env", ft_strlen(line[0])))
		ft_env(listas->linked_env, line[1]);
	if (!ft_strncmp(line[0], "unset", ft_strlen(line[0])))
		ft_unset(line[1], &listas->linked_env, &listas->sort); //unset da seg fault quando se tenta libertar o primeiro da lista ver -> first_unset()
	return (0);
}
