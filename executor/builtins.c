/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:05:27 by jmendes           #+#    #+#             */
/*   Updated: 2021/11/16 19:48:02 by rimartin         ###   ########.fr       */
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

int	vars_echo(char *line, t_lista *lst)
{
	int		index;
	t_lista	*current;

	index = 0;
	current = lst;
	while (current != NULL)
	{
		if (ft_strncmp(current->content, line, ft_strlen(line)) == 0)
		{
			index = char_check(current->content, '=');
			printf("%s\n", ft_substr(current->content, index, ft_strlen(current->content) - index));
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	echo(char **line, int flag_n, int error_code, t_listas *listas)
{
	int	index;

	index = 1;
	if (flag_n == 1)
		index = 2;
	while (line[index])
	{
		if (line[index][0] == '$')
		{
			if (line[index][1] != '?')
			{
				if (vars_echo(line[index], listas->linked_env) == 0)
					return (0);
			}
		}
		if (line[index + 1])
			printf(" ");
		index++;
	}
	if (flag_n == 0)
		printf("\n");
	return (error_code);
}

int	exit_builtin(t_parse *st, t_lista *env, t_node **node)
{
	fprintf(stderr, "teste 5\n");
	if (env)
		ft_lstclear((t_list **)&env, free);
	free(st->exp);
	free_nodes(node);
	return (0);
}

int	builtins(t_parse *st, t_node **node, char **env, char **line)
{
	int			echo_n;
	int			error_code;
	t_listas	*listas;

	echo_n = 0;
	error_code = 3;
	listas = NULL;
	printf("teste 69\n");
	list_init(listas, env);
	line = ft_split_quotes((*node)->cmd);
	printf("line[0] %s sssss\n", line[0]);
	if (ft_strncmp(line[0], "cd", ft_strlen(line[0])) == 0)
		error_code = cd(line[1]);
	else if (ft_strncmp(line[0], "pwd", ft_strlen(line[0])) == 0)
		error_code = pwd();
	else if (ft_strncmp(line[0], "echo", ft_strlen(line[0])) == 0)
	{
		fprintf(stderr, "Entrou?\n");
		if (ft_strncmp(line[1], "-n", ft_strlen(line[1]) == 0))
			echo_n = 1;
		echo(line, echo_n, error_code, listas);
	}
	if (ft_strncmp(line[0], "exit", ft_strlen(line[0])) == 0)
		exit_builtin(st, listas->linked_env, node);
	if (ft_strncmp(line[0], "export", ft_strlen(line[0])) == 0)
		ft_export(line[1], listas->linked_env, listas->sort);
	if (ft_strncmp(line[0], "env", ft_strlen(line[0])) == 0)
		ft_env(listas->linked_env);
	if (ft_strncmp(line[0], "unset",ft_strlen(line[0])) == 0)
		ft_unset(line[0], listas->linked_env, listas->sort);//unset da seg fault quando se tenta libertar o primeiro da lista ver -> first_unset()
	return (0);
}
