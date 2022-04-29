/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:37:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/20 03:58:02 by rimartin         ###   ########.fr       */
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

void	init_all(t_listas **listas, char **env, int ac, char **av)
{
	// struct sigaction	sa;
	// struct sigaction	sa_1;
	// struct termios		term;

	(void)ac;
	(void)av;
	// tcgetattr(0, &term);
	// term.c_lflag &= ~ECHOCTL;
	// tcsetattr(0, TCSANOW, &term);
	// sa.sa_handler = &sig_int;
	// sa_1.sa_handler = SIG_IGN;
	// sa.sa_flags = SA_RESTART;
	// sigaction(SIGINT, &sa, NULL);
	// sigaction(SIGQUIT, &sa_1, NULL);
	list_init(listas, env);
}

int	main(int ac, char **av, char **env)
{
	static t_node	*empty_node;
	t_listas		*listas;
	char			**split_var;

	init_all(&listas, env, ac, av);
	while (1)
	{
		split_var = NULL;
		g_gl.node = empty_node;
		if (get_readline_and_history() == -1)
			continue ;
		abstract_tree_parser(&g_gl.node, &g_gl.exp, &g_gl.n_pipes,
			listas->linked_env);
		if (is_empty_tree(g_gl.node) && g_gl.node->cmd != NULL)
			split_var = split_quotes(g_gl.node->cmd, 1);
		if (g_gl.node->cmd != NULL && is_empty_tree(g_gl.node)
			&& is_builtin(split_var))
			builtins(g_gl.node, listas, split_var);
		else
			ft_exec(g_gl.node, g_gl.n_pipes, listas->linked_env);
		free_nodes(g_gl.node, &g_gl.exp);
		if (split_var)
			free_dp(split_var);
	}
	return (0);
}
