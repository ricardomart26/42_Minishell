/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:05:27 by jmendes           #+#    #+#             */
/*   Updated: 2021/11/23 18:56:07 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	path[1040];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
		return (1);
	return (0);
}

int	cd(char *path)
{
	if (chdir(path) != 0)
	{
		printf("ERROR: NO DIRECTORY");
		return (0);
	}
	return (0);
}

int	exit_builtin(t_parser *parser, t_lista *env, t_node **node)
{
	if (env)
		ft_lstclear((t_list **)&env, free);
	free_nodes(node, parser);
	return (0);
}

int	builtins(t_parser *parser, t_node **node, t_listas *listas, char **line)
{
	int			echo_n;

	echo_n = 0;
	if (!ft_strncmp(line[0], "cd", ft_strlen(line[0])))
		g_error_code = cd(line[1]);
	else if (!ft_strncmp(line[0], "pwd", ft_strlen(line[0])))
		g_error_code = pwd();
	else if (!ft_strncmp(line[0], "echo", ft_strlen(line[0])))
	{
		if (!ft_strncmp(line[1], "-n", ft_strlen(line[1])))
			echo_n = 1;
		echo(line, echo_n, g_error_code, listas);
	}
	if (!ft_strncmp(line[0], "exit", ft_strlen(line[0])))
		exit_builtin(parser, listas->linked_env, node);
	if (!ft_strncmp(line[0], "export", ft_strlen(line[0])))
		ft_export(line[1], listas->linked_env, listas->sort);
	if (!ft_strncmp(line[0], "env", ft_strlen(line[0])))
		ft_env(listas->linked_env);
	if (!ft_strncmp(line[0], "unset", ft_strlen(line[0])))
		ft_unset(line[0], listas->linked_env, listas->sort); //unset da seg fault quando se tenta libertar o primeiro da lista ver -> first_unset()
	return (0);
}
