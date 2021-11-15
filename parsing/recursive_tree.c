/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:48:39 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/15 01:30:53 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*rec_node_tree_init(char *exp, bool pipe, bool final, t_limit *l)
{
	t_node	*node;
	int		i;
	int		size;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	if (l->start == 0)
		node->first_cmd = true;
	node->type = COMMAND;
	size = l->end - l->start;
	node->end_of_tree = false;
	if (final)
		node->end_of_tree = true;
	node->cmd = malloc(size + 1);
	node->pipe = pipe;
	i = -1;
	while (++i < size)
		node->cmd[i] = exp[l->start + i];
	node->cmd[i] = '\0';
	return (node);
}

/**
 * 
 * @definition: Pipe parser vai dividir os commandos até ao pipe "|", atraves do
 * start e end. Enquanto nao chegar ao ultimo commando adicionamos o node a 
 * esquerda, o ultimo comando adicionamos a direita e indicamos o final da tree 
 * com a variavel end_of_true para conseguirmos iterar pela tree e sabermos o 
 * final da mesma. 
 * 
 * @params: node -> Pointer para o endereco do inicio da abstract tree
 * st -> Estrutura geral 
 *  
 * @return_value: Vai preencher o node com os comandos na left e right tree
 * 
 */

void	handle_ast_nodes(t_node *node, char *exp, t_limit *l, int pipes)
{
	t_node	*temp;

	temp = node;
	temp->type = PIPESS;
	if (pipes > 1)
	{
		printf("TESTEEEEE\n");
		temp->l = rec_node_tree_init(exp, true, false, l);
		temp->r = malloc(sizeof(t_node));
		temp->r->l = NULL;
		temp->r->end_of_tree = false;
		temp->r->type = PIPESS;
	}
	else if (pipes == 1)
		temp->l = rec_node_tree_init(exp, true, true, l);
	else
		temp->r = rec_node_tree_init(exp, false, true, l);
}

/**
 * 
 * @definition: Divide every cmd before and after the pipe, the algorithm used 
 * was AST (Abstract Syntax Tree), when only one command just save in the First
 * node without left and rigth nodes. When has pipes divide them into the
 * left goes through the rigth node until the last command, when it finds
 * the last command just add the command to the rigth node of the tree.
 * Ex.
 * 
 * One command:     
 * node = ls -la
 * 						node = ls -la
 * Two commands
 * node->l = ls -la
 * node->r = wc -l
 * 
 * 							node
 * 						  /		\
 * 			       left  /		 \ rigth
 * 					  ls -la	wc - l
 * 
 * Three commands:
 * node->l = ls -la
 * node = node->r
 * node->l = grep "*.txt"
 * node->r = wc -l
 * 
 * 							PIPE
 * 						   /	\
 * 				    left  /		 \ rigth
 * 					   ls -la	PIPE
 * 								/  \
 * 						 left  /    \ rigth
 * 							grep   wc -l
 * 
 * @params: char *exp;
 *  
 * @return_value: Returns the node with all the commands inside.
 * 
 */

void	rec_parse_pipes(char *exp, t_node *node, t_limit *l, int pipes)
{
	t_token	curr_token;
	t_parse	st;

	st.open_dq = 0;
	st.open_q = 0;
	while (exp[l->end])
	{
		st.c = exp[l->end];
		curr_token = get_token(st.c, 0);
		check_quotes(curr_token, &st.open_dq, &st.open_q);
		if (curr_token == PIPE && (!st.open_dq && !st.open_q))
		{
			handle_ast_nodes(node, exp, l, pipes);
			l->end += 1;
			l->start = l->end;
			if (node->l->end_of_tree != true)
				rec_parse_pipes(exp, node->r, l, pipes - 1);
			else
				rec_parse_pipes(exp, node, l, pipes - 1);
			return ;
		}
		l->end++;
	}
	handle_ast_nodes(node, exp, l, pipes);
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
		only_one_cmd(st->exp, node);
	else
		rec_parse_pipes(st->exp, node, &l, st->n_pipes);
	if (st->n_pipes == 1)
		node->type = PIPESS;
	parse_red(st, &root);
	if (st->amount_red)
		divide_cmd_and_file(&node, st);
	return (root);
}
