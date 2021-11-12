/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:05:27 by jmendes           #+#    #+#             */
/*   Updated: 2021/11/12 21:44:24 by rimartin         ###   ########.fr       */
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

int	exit_builtin(t_parse *st, t_lista *env, t_node **node)
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
	
	if (!new_ps && ps)
		new_ps = ps;
	return (new_ps);
}

void list_sort(t_lista *lst)
{
	t_lista *current;
	t_lista *after;
	char *temp;
	int index;

	index = 0;
	current = lst;
	while (current->next != NULL)
	{
		after = current->next;
		while (after != NULL)
		{
			index = 0;
			if ((unsigned char)current->content[0] > (unsigned char)after->content[0])
			{
				temp = ft_strdup(current->content);
				current->content = ft_strdup(after->content);
				after->content = ft_strdup(temp);
			}
			else if ((unsigned char)current->content[0] == (unsigned char)after->content[0])
			{
				while ((unsigned char)current->content[index] == (unsigned char)after->content[index])
				{
					index++;
					if ((unsigned char)current->content[index] > (unsigned char)after->content[index])
					{
						temp = ft_strdup(current->content);
						current->content = ft_strdup(after->content);
						after->content = ft_strdup(temp);
					}
					else if ((unsigned char)current->content[index] < (unsigned char)after->content[index])
						break;
				}
			}
	
			after = after->next;
		}
		printf("declare -x %s\n", current->content);
		current = current->next;
	}
	printf("declare -x %s\n", current->content);
}

int export(char *var, t_lista *envp, t_lista *sort)
{
	if (var == NULL)
		list_sort(sort);
	else
	{
		if (copy_check(var, sort, envp) == 0)
		{
			ft_lstadd_back((void *)&sort, ft_lstnew((void *)ft_strdup(var)));
			if (char_check(var, '=') != -1)
				ft_lstadd_back((void *)&envp, ft_lstnew((void *)ft_strdup(var)));
		}
	}
	return (0);
}

int	ft_env(t_lista *lst)
{
	t_lista *current;

	current = lst;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}

void 	list_init(t_listas *listas, char **env)
{
	int index;

	index = 0;
	while (env[index] != NULL)
	{
		ft_lstadd_back((void *)&listas->linked_env, ft_lstnew((void *)ft_strdup(env[index])));
		ft_lstadd_back((void *)&listas->sort, ft_lstnew((void *)ft_strdup(env[index])));
		index++;
	}
}

int	builtins(t_parse *st, t_node **node, char **env)
{
	int		echo_n;
	int		error_code;
	char	**line;
	t_listas	*listas;
	
	echo_n = 0;
	error_code = 3;
	listas = NULL;
	list_init(listas, env);
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
		exit_builtin(st, listas->linked_env, node);
	if (ft_strncmp(line[0], "export",ft_strlen(line[0])) == 0)
		export(line[1], listas->linked_env, listas->sort);
	if (ft_strncmp(line[0], "env",ft_strlen(line[0])) == 0)
		ft_env(listas->linked_env);
	return (0);
}
