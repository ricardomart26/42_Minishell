/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:05:27 by jmendes           #+#    #+#             */
/*   Updated: 2021/11/27 16:42:33 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	path[1040];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
		g.error_code = GENERAL_ERROR;
}


char	*get_home_var(t_lista *lst_env, char *path)
{
	t_lista *temp;

	temp = lst_env;
	while (ft_strncmp(temp->content, "HOME", 4) && temp != NULL)
		temp = temp->next;
	if (!ft_strncmp(temp->content, "HOME", 4))
	{
		if (path[1] && path[1] == '/')
			return (ft_strjoin(temp->content + 5, path + 1));
		return (temp->content + 5);
	}
	return (NULL);
}

void	cd(char *path, t_lista *lst_envp)
{
	if (path[0] == '~')
		path = ft_strdup(get_home_var(lst_envp, path));
	if (chdir(path) != 0)
	{
		printf("ERROR: NO DIRECTORY");
		g.error_code = GENERAL_ERROR;
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
		cd(line[1], listas->linked_env);
	else if (!ft_strncmp(line[0], "pwd", ft_strlen(line[0])))
		pwd();
	else if (!ft_strncmp(line[0], "echo", ft_strlen(line[0])))
	{
		if (line[1] && !ft_strncmp(line[1], "-n", ft_strlen(line[1])))
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
		ft_unset(line[1], &listas->linked_env, &listas->sort);
	return (0);
}
