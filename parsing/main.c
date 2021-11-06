/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:37:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/06 20:12:43 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	parse_cmd(char *exp, t_node *node)
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

t_node	*abstract_tree_parser(t_node *node, t_parse *st)
{
	t_limit	l;
	t_node	*root;

	l.start = 0;
	l.end = 0;
	st->n_pipes = count_tokens(st, PIPE);
	st->amount_red = count_tokens(st, REDIRECTION);
	node = malloc(sizeof(t_node));
	root = node;
	if (st->n_pipes == 0)
		parse_cmd(st->exp, node);
	else
		rec_parse_pipes(st->exp, node, &l, st->n_pipes);
	parse_red(st, &root);
	if (st->amount_red)
		divide_cmd_and_file(&node, st);
	return (root);
}

void	free_nodes(t_node *node)
{
	if (is_empty_tree(node))
	{
		free(node);
		return ;
	}
	if (node->r == PIPESS)
	{
		free(node->l);
		free_nodes(node->r);
	}
	free(node->l);
	free(node->r);
}

int	main(int ac, char **av, char **env)
{
	t_global	g;

	(void) ac;
	(void) av;
	g.node = NULL;
	g.env = env;
	g.linked_env = env_to_linked_list(env);
	while (1)
	{
		g.ps = g_empty_st;
		g.node = g_empty_node;
		g.ps.exp = readline("Enter a command: ");
		while (find_c_in_str(*g.ps.exp, SPACES))
			g.ps.exp++;
		if (ft_strlen(g.ps.exp) == 0)
			continue ;
		add_history(g.ps.exp);
		g.ps.exp = expand_vars(g.ps.exp, 0, -1, false);
		g.node = abstract_tree_parser(g.node, &g.ps);
		exec(g.node, g.env);
		free(g.ps.exp);
		free_nodes(g.node);
	}
	return (0);
}
