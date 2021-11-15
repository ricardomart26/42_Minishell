/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:37:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/14 16:48:29 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	*singleton_ps(t_parse *ps ) // Design pattern
{
	static t_parse *new_ps = NULL;
	
	if (!new_ps && ps)
		new_ps = ps;
	return (new_ps);
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
	node->cmd = ft_strdup(exp);
}

int	get_readline_and_history(t_global *g)
{
	g->ps.exp = readline("Enter a command: ");
	while (find_c_in_str(*g->ps.exp, SPACES))
		g->ps.exp++;
	if (ft_strlen(g->ps.exp) == 0)
		return (-1);
	add_history(g->ps.exp);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_global		g;
	static t_parse	empty_ps;
	static t_node	*empty_node;

	(void) ac;
	(void) av;
	g.ps.env = ft_strdup_dp((const char **)env);
	while (1)
	{
		g.ps = empty_ps;
		g.node = empty_node;
		if (get_readline_and_history(&g) == -1)
			continue ;
		expand_vars(g.ps.exp, 0, -1, false);
		g.node = abstract_tree_parser(g.node, &g.ps);
		singleton_ps(&g.ps);
		my_exec(g.node, &g.ps, env);
		free(g.ps.exp);
		g.ps.exp = NULL;
		free_nodes(&g.node);
	}
	return (0);
}
