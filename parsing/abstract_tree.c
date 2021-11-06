/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:15:20 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/04 22:32:10 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_node	*node_tree_init(t_parse *st, bool pipe, bool final)
{
	t_node	*node;
	int		i;
	int		size;

	node = malloc(sizeof(t_node));
	size = st->end - st->start;
	if (final)
		node->end_of_tree = true;
	else
		node->end_of_tree = false;
	node->cmd = malloc(size + 1);
	node->pipe = pipe;
	i = -1;
	while (++i < size)
		node->cmd[i] = st->exp[st->start + i];
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

int	pipe_parser(t_node **node, t_parse *st, int pipes)
{
	t_node	*temp;

	temp = *node;
	if (st->start == 0)
		temp->first_cmd = true;
	else
		temp->first_cmd = false;
	while (temp->l != NULL && temp->l->end_of_tree != true)
		temp = temp->r;
	if (pipes > 1)
	{
		temp->l = node_tree_init(st, true, false);
		temp->r = malloc(sizeof(t_node));
		temp->r->l = NULL;
		temp->r->end_of_tree = false;
	}
	else if (pipes == 1)
		temp->l = node_tree_init(st, true, true);
	else
		temp->r = node_tree_init(st, false, true);
	return (pipes - 1);
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
 * 							node
 * 						   /	\
 * 				    left  /		 \ rigth
 * 					   ls -la	node
 * 								/  \
 * 						 left  /    \ rigth
 * 							grep   wc -l
 * 
 * @params: t_parse st {
 * 	int		n_pipes;
 *	int		amount_red;
 *	bool	open_q;
 *	bool	open_dq;
 *	int		c;
 *	int		next;
 *	char	*exp;
 * };
 *  
 * @return_value: Returns the node with all the commands inside.
 * 
 */

void	parse_exp_pipes(t_parse *st, t_node **node)
{
	t_token		curr_token;
	int			pipes;

	pipes = st->n_pipes;
	st->end = 0;
	st->start = 0;
	*node = malloc(sizeof(t_node));
	(*node)->n_red = 0;
	(*node)->l = NULL;
	while (st->exp[st->end])
	{
		st->c = st->exp[st->end];
		curr_token = get_token(st->c, 0);
		check_quotes(curr_token, &st->open_dq, &st->open_q);
		if (curr_token == PIPE && (!st->open_dq && !st->open_q))
		{
			pipes = pipe_parser(node, st, pipes);
			st->end += 1;
			st->start = st->end;
			continue ;
		}
		st->end++;
	}
	pipes = pipe_parser(node, st, pipes);
}
