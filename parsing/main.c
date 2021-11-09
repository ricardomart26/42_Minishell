/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:37:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/09 22:55:31 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @definition: Conta a quantidade de tokens na expressao recebida da readline
 * Example: Se o token for "\", entao o comando: ls -la | wc -l, vai contar como 
 * 1. 
 * 
 * @params: st -> Estrutura geral (So para nao ter que iniciar certas variaveis
 * em cada funcao, e para andar com a expressao recebida do readline pelas
 * funcoes)
 * st -> find_token vai ser o token que queremos contar
 *  
 * @return_value: Retorna o numero de tokens encontrado na expressao
 * 
 */

int	count_tokens(t_parse *st, t_token find_token)
{
	int		i;
	int		counter;
	t_token	token;

	i = -1;
	counter = 0;
	while (st->exp[++i])
	{
		st->c = st->exp[i];
		if (st->exp[i + 1])
			st->next = st->exp[i + 1];
		else
			st->next = 0;
		token = get_token(st->c, st->next);
		check_quotes(token, &st->open_dq, &st->open_q);
		if (token == find_token && (!st->open_dq && !st->open_q))
			counter++;
	}
	return (counter);
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

void	free_nodes(t_node *node, t_node *old)
{
	if (is_empty_tree(node))
	{
		free(node);
		return ;
	}
	if (node->r->type == PIPESS)
	{
		printf("node type %d\n", node->r->type);
		if (old != NULL)
			free(old);
		free(node->l);
		free_nodes(node->r, node);
	}
	free(node->l);
	free(node->r);
}

void	init_variables(t_global *g)
{
	static t_parse	empty_ps;
	static t_node	*empty_node;
	
	g->ps = empty_ps;
	g->node = empty_node;
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
	t_global	g;

	(void) ac;
	(void) av;

	g.env = env;
	g.linked_env = env_to_linked_list(env);
	while (1)
	{
		init_variables(&g);
		if (get_readline_and_history(&g) == -1)
			continue ;
		expand_vars(g.ps.exp, 0, -1, false);
		g.node = abstract_tree_parser(g.node, &g.ps);
		singleton_ps(&g.ps);
		singleton_env(g.linked_env);
		printf("linked %s\n", g.linked_env->keyword);
		exec(g.node, g.env);
		free(g.ps.exp);
		g.ps.exp = NULL;
		free_nodes(g.node, NULL);
	}
	return (0);
}
