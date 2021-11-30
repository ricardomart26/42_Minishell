/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:37:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/30 16:19:18 by rimartin         ###   ########.fr       */
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
	node->r = NULL;
	node->end_of_tree = true;
	node->type = IS_A_COMMAND;
	node->has_heredoc = false;
	node->cmd = ft_strdup(exp);
	get_red(node, node->cmd, false, false);
}

int	get_readline_and_history(void)
{
	g_gl.exp = readline("Enter a command: ");
	if (!g_gl.exp)
		exit(1);
	while (find_c_in_str(*g_gl.exp, SPACES))
		g_gl.exp++;
	if (ft_strlen(g_gl.exp) == 0)
		return (-1);
	add_history(g_gl.exp);
	if (not_valid_line((const char *)g_gl.exp))
		return (-1);
	return (0);
}

void	init_all(t_listas **listas, char **env)
{
	struct sigaction	sa;
	struct sigaction	sa_1;
	struct termios		term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	sa.sa_handler = &sig_int;
	sa_1.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	list_init(listas, env);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa_1, NULL);
}

int	main(int ac, char **av, char **env)
{
	static t_node	*empty_node;
	t_listas		*listas;

	(void) ac;
	(void) av;
	init_all(&listas, env);
	while (1)
	{
		g_gl.node = empty_node;
		if (get_readline_and_history() == -1)
			continue ;
		abstract_tree_parser(&g_gl.node, &g_gl.exp, &g_gl.n_pipes,
			listas->linked_env);
		if (g_gl.node->cmd != NULL && is_empty_tree(g_gl.node)
			&& is_builtin(split_quotes(g_gl.node->cmd, 1)))
			builtins(&g_gl.node, listas,
				split_quotes(g_gl.node->cmd, 1));
		else
			ft_exec(g_gl.node, g_gl.n_pipes, env);
		free_nodes(&g_gl.node, &g_gl.exp);
	}
	return (0);
}
