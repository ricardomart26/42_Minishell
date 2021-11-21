/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:48:39 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/21 17:59:31 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*rec_node_tree_init(char *exp, bool pipe, bool final, t_vars_x_y *vars)
{
	t_node	*node;
	int		i;
	int		size;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	if (vars->x == 0)
		node->first_cmd = true;
	node->type = COMMAND;
	size = vars->y - vars->x;
	node->end_of_tree = false;
	if (final)
		node->end_of_tree = true;
	node->cmd = malloc(size + 1);
	node->pipe = pipe;
	i = -1;
	while (++i < size)
		node->cmd[i] = exp[vars->x + i];
	node->cmd[i] = '\0';
	return (node);
}

/**
 * 
 * @definition: Pipe parser vai dividir os commandos até ao pipe "|", atraves do
 * x e end. Enquanto nao chegar ao ultimo commando adicionamos o node a 
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

void	handle_ast_nodes(t_node *node, char *exp, t_vars_x_y *vars, int pipes)
{
	t_node	*temp;

	temp = node;
	temp->type = PIPESS;
	if (pipes > 1)
	{
		temp->l = rec_node_tree_init(exp, true, false, vars);
		temp->r = malloc(sizeof(t_node));
		temp->r->l = NULL;
		temp->r->end_of_tree = false;
		temp->r->type = PIPESS;
	}
	else if (pipes == 1)
		temp->l = rec_node_tree_init(exp, true, true, vars);
	else
		temp->r = rec_node_tree_init(exp, false, true, vars);
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

void	parsing_of_pipes(char *exp, t_node *node, t_vars_x_y *vars, int pipes)
{
	t_token		curr_token;
	t_parser	parser;

	parser.open_dq = 0;
	parser.open_q = 0;
	while (exp[vars->y])
	{
		parser.c = exp[vars->y];
		curr_token = get_token(parser.c, 0);
		check_quotes(curr_token, &parser.open_dq, &parser.open_q);
		if (curr_token == PIPE && (!parser.open_dq && !parser.open_q))
		{
			handle_ast_nodes(node, exp, vars, pipes);
			vars->y += 1;
			vars->x = vars->y;
			if (node->l->end_of_tree != true)
				parsing_of_pipes(exp, node->r, vars, pipes - 1);
			else
				parsing_of_pipes(exp, node, vars, pipes - 1);
			return ;
		}
		vars->y++;
	}
	handle_ast_nodes(node, exp, vars, pipes);
}

t_node	*abstract_tree_parser(t_node *node, t_parser *parser)
{
	t_vars_x_y	vars;
	t_node		*root;

	vars.x = 0;
	vars.y = 0;
	parser->n_pipes = count_tokens(parser, PIPE);
	parser->n_of_redirections = count_tokens(parser, REDIRECTION);
	node = malloc(sizeof(t_node));
	root = node;
	if (parser->n_pipes == 0)
		only_one_cmd(parser->exp, node);
	else
		parsing_of_pipes(parser->exp, node, &vars, parser->n_pipes);
	if (parser->n_pipes == 1)
		node->type = PIPESS;
	parse_red(parser, &root);
	if (parser->n_of_redirections != 0)
		divide_cmd_and_file(&node, parser);
	return (root);
}
