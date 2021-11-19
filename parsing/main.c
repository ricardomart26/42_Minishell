/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:37:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/19 22:04:03 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*singleton_ps(t_parser *helper)
{
	static t_parser	*new_helper = NULL;

	if (!new_helper && helper)
		new_helper = helper;
	return (new_helper);
}

/**
 * 
 * @definition: When only one command without pipes, store it inside the node
 * without the left and rigth node.
 * 
 * @params: exp -> command passed by readline
 * t_node -> Pointer para o endereco do inicio da arvore
 *  
 * @return_value: returns the node with the command inside
 * 
 */

void	only_one_cmd(char *exp, t_node *node)
{
	node->n_red = 0;
	node->l = NULL;
	node->l = NULL;
	node->r = NULL;
	node->end_of_tree = true;
	node->first_cmd = true;
	node->type = COMMAND;
	node->has_heredoc = false;
	node->cmd = ft_strdup(exp);
}

int	get_readline_and_history(t_global *g)
{
	g->parser.exp = readline("Enter a command: ");
	while (find_c_in_str(*g->parser.exp, SPACES))
		g->parser.exp++;
	if (ft_strlen(g->parser.exp) == 0)
		return (-1);
	add_history(g->parser.exp);
	return (0);
}

char	*expand_vars2(char *line, t_lista *current)
{
	int	start;

	start = 0;
	if (line[0] == '$' && ft_strlen(line) != 1)
	{
		line = ft_substr(line, 1, ft_strlen(line) - 1);
		while (ft_strncmp(current->content, line, ft_strlen(line) != 0 
				&& current != NULL))
				current = current->next;
		if (ft_strncmp(current->content, line, ft_strlen(line)) == 0)
		{
			start = char_check(current->content, '=');
			line = ft_substr(current->content, start + 1, ft_strlen(current->content));
		}
	}
	return (line);
}

char	*expand_vars(char *line_var, t_lista *lst_envp)
{
	t_lista	*current;
	char	**line;
	int		index;

	index = 0;
	current = lst_envp;
	line = ft_split(line_var, ' ');
	while (line[index])
	{
		line[index] = expand_vars2(line[index], current);
		index++;
	}
	index = 1;
	while (line[index])
	{
		line[0] = ft_strjoin(line[0], ft_strjoin(" ", line[index]));
		index++;
	}
	return (line[0]);
}

int	main(int ac, char **av, char **env)
{
	t_global		g;
	static t_parser	empty_parser;
	static t_node	*empty_node;

	(void) ac;
	(void) av;
	while (1)
	{
		g.parser = empty_parser;
		g.node = empty_node;
		if (get_readline_and_history(&g) == -1)
			continue ;
		// if (validate_line(g.parser.exp) == -1)
		// 	error_msg("Wrong input\n");
		// expand_vars(g.parser.exp, 0, -1, false);
		g.node = abstract_tree_parser(g.node, &g.parser);
		if (g.node->cmd != NULL && is_empty_tree(g.node)
			&& is_builtin(ft_split_quotes(g.node->cmd)))
			builtins(&g.parser, &g.node, env, ft_split_quotes(g.node->cmd));
		my_exec(g.node, &g.parser, env);
		free(g.parser.exp);
		g.parser.exp = NULL;
		free_nodes(&g.node);
	}
	return (0);
}
