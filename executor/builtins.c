/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:05:27 by jmendes           #+#    #+#             */
/*   Updated: 2021/11/20 12:55:40 by rimartin         ###   ########.fr       */
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
		return (1);
	}
	return (0);
}

int	exit_builtin(char *exp, t_lista *env, t_node **node)
{
	if (env)
		ft_lstclear((t_list **)&env, free);
	free(exp);
	free_nodes(node);
	return (0);
}

int	builtins(char *exp, t_node **node, char **env, char **line)
{
	int			echo_n;
	int			error_code;
	t_listas	*listas;

	echo_n = 0;
	error_code = 3;
	if (!ft_strncmp(line[0], "cd", ft_strlen(line[0])))
		error_code = cd(line[1]);
	else if (!ft_strncmp(line[0], "pwd", ft_strlen(line[0])))
		error_code = pwd();
	else if (!ft_strncmp(line[0], "echo", ft_strlen(line[0])))
	{
		if (!ft_strncmp(line[1], "-n", ft_strlen(line[1])))
			echo_n = 1;
		echo(line, echo_n, error_code, listas);
	}
	if (!ft_strncmp(line[0], "exit", ft_strlen(line[0])))
		exit_builtin(exp, listas->linked_env, node);
	if (!ft_strncmp(line[0], "export", ft_strlen(line[0])))
		ft_export(line[1], listas->linked_env, listas->sort);
	if (!ft_strncmp(line[0], "env", ft_strlen(line[0])))
		ft_env(listas->linked_env);
	if (!ft_strncmp(line[0], "unset", ft_strlen(line[0])))
		ft_unset(line[0], listas->linked_env, listas->sort); //unset da seg fault quando se tenta libertar o primeiro da lista ver -> first_unset()
	return (0);
}
