/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:05:27 by jmendes           #+#    #+#             */
/*   Updated: 2021/11/09 20:35:06 by rimartin         ###   ########.fr       */
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

/**
 * 
 * @things_missing: 
 * 
 * - Sem argumentos (Ex. cd ) vai para a home
 * - Com ~ vai para a home tambem
 * - cd -
 */

int	cd(char *path)
{
	if (chdir(path) != 0)
	{
		printf("ERROR: NO DIRECTORY");
		return (1);
	}
	return (0);
}

int	echo(char **line, int flag_n, int error_code)
{
	int	index;

	index = 1;
	if (flag_n == 1)
		index = 2;
	while (line[index])
	{
		if (line[index + 1])
			printf(" ");
		index++;
	}
	if (flag_n == 0)
		printf("\n");
	return (error_code);
}

int	exit_builtin(t_parse *st, t_env **env, t_node **node)
{
	t_node	*tmp;

	if (env)
		ft_lstclear_env(env, free);
	free(st->exp);
	if (is_empty_tree(*node))
		return (free_node(node));
	while ((*node)->end_of_tree != true)
	{
		tmp = (*node)->l;
		free_node(&tmp);
		tmp = (*node);
		(*node) = (*node)->r;
		free(tmp);
	}
	tmp = (*node)->l;
	free_node(&tmp);
	tmp = (*node)->r;
	free_node(&tmp);
	return (0);
}

t_parse	*singleton_ps(t_parse *ps) // Design pattern
{
	static t_parse *new_ps = NULL;
	
	if (new_ps == NULL && ps != NULL)
		new_ps = ps;
	return (new_ps);
}

t_env	*singleton_env(t_env *link) // Design pattern
{
	static t_env *new_link = NULL;
	
	if (new_link == NULL && link != NULL)
		new_link = link;
	return (new_link);
}


int	builtins(t_parse *st, t_env **env, t_node **node)
{
	int		echo_n;
	int		error_code;
	char	**line;

	echo_n = 0;
	error_code = 3;
	line = ft_split_quotes((*node)->cmd, ' ');
	if (ft_strncmp(line[0], "cd", ft_strlen(line[0])) == 0)
		error_code = cd(line[1]);
	else if (ft_strncmp(line[0], "pwd", ft_strlen(line[0])) == 0)
		error_code = pwd();
	else if (ft_strncmp(line[0], "echo", ft_strlen(line[0])) == 0)
	{
		if (ft_strncmp(line[1], "-n", ft_strlen(line[1]) == 0))
			echo_n = 1;
		echo(line, echo_n, error_code);
	}
	if (ft_strncmp(line[0], "exit", ft_strlen(line[0])) == 0)
		exit_builtin(st, env, node);
	return (0);
}
