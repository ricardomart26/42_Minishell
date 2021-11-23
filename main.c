/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:37:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/23 16:06:30 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	node->type = IS_A_COMMAND;
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
	if (not_valid_line((const char *)g->parser.exp))
		return (-1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_global		g;
	static t_parser	empty_parser;
	static t_node	*empty_node;
	t_listas		*listas;

	(void) ac;
	(void) av;
	listas = NULL;
	list_init(&listas, env);
	while (1)
	{
		g.parser = empty_parser;
		g.node = empty_node;
		if (get_readline_and_history(&g) == -1)
			continue ;
		g.parser.exp = expand_vars(g.parser.exp, listas->linked_env);
		abstract_tree_parser(&g.node, &g.parser);
		if (g.node->cmd != NULL && is_empty_tree(g.node)
			&& is_builtin(split_quotes(g.node->cmd, 1)))
			builtins(&g.parser, &g.node, listas, split_quotes(g.node->cmd, 1));
		else
			ft_exec(g.node, g.parser.n_pipes, env);
		free_nodes(&g.node, &g.parser);
	}
	return (0);
}
