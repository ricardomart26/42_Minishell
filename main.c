/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:37:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/25 21:15:10 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <readline/history.h>

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

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	//if (sig == SIGQUIT)
}

int	main(int ac, char **av, char **env)
{
	//struct sigaction sa;
	//sa.sa_handler = &sig_int;
	//sa.sa_flags = SA_RESTART;
	t_global		g;
	tcgetattr(0, &g.term);
	g.term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &g.term);
	static t_parser	empty_parser;
	static t_node	*empty_node;
	t_listas		*listas;

	(void) ac;
	(void) av;
	listas = NULL;
	list_init(&listas, env);
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_int);
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
