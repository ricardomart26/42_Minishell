/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:37:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/17 23:38:07 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_others	*singleton_ps(t_others *helper)
{
	static t_others	*new_helper = NULL;

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
	node->fd_h = -1;
	node->has_heredoc = false;
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

// int	check_if_its_command()
// {
	
// }


// // int	validate_line(char *exp)
// // {
// // 	int		error_code;
// // 	char	**splited;
// // 	int		i;

		
// // }

int	main(int ac, char **av, char **env)
{
	t_global		g;
	static t_others	empty_ps;
	static t_node	*empty_node;

	(void) ac;
	(void) av;
	// Fazer os sinais
	while (1)
	{
		g.ps = empty_ps;
		g.node = empty_node;
		if (get_readline_and_history(&g) == -1)
			continue ;
		// if (validate_line(g.ps.exp) == -1)
		// 	error_msg("Wrong input\n");
		// expand_vars(g.ps.exp, 0, -1, false);
		g.node = abstract_tree_parser(g.node, &g.ps);
		singleton_ps(&g.ps);
		my_exec(g.node, &g.ps, env);
		free(g.ps.exp);
		g.ps.exp = NULL;
		free_nodes(&g.node);
	}
	return (0);
}
