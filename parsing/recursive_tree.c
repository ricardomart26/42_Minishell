/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:48:39 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/22 23:48:25 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*rec_node_tree_init(char *exp, bool pipe, bool final, t_vars_i_j *vars)
{
	t_node	*node;
	int		i;
	int		size;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	if (vars->i == 0)
		node->first_cmd = true;
	node->type = IS_A_COMMAND;
	size = vars->j - vars->i;
	node->end_of_tree = false;
	if (final)
		node->end_of_tree = true;
	node->cmd = malloc(size + 1);
	node->pipe = pipe;
	i = -1;
	while (++i < size)
		node->cmd[i] = exp[vars->i + i];
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

void	handle_ast_nodes(t_node *node, char *exp, t_vars_i_j *vars, int pipes)
{
	t_node	*temp;

	temp = node;
	temp->type = IS_A_PIPE;
	if (pipes > 1)
	{
		temp->l = rec_node_tree_init(exp, true, false, vars);
		temp->r = malloc(sizeof(t_node));
		temp->r->l = NULL;
		temp->r->end_of_tree = false;
		temp->r->type = IS_A_PIPE;
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

void	parsing_of_pipes(char *exp, t_node *node, t_vars_i_j *vars, int pipes)
{
	t_token		curr_token;
	t_parser	parser;

	parser.open_dq = 0;
	parser.open_q = 0;
	while (exp[vars->j])
	{
		parser.c = exp[vars->j];
		curr_token = get_token(parser.c, 0);
		check_quotes(curr_token, &parser.open_dq, &parser.open_q);
		if (curr_token == PIPE && (!parser.open_dq && !parser.open_q))
		{
			handle_ast_nodes(node, exp, vars, pipes);
			vars->j += 1;
			vars->i = vars->j;
			if (node->l->end_of_tree != true)
				parsing_of_pipes(exp, node->r, vars, pipes - 1);
			else
				parsing_of_pipes(exp, node, vars, pipes - 1);
			return ;
		}
		vars->j++;
	}
	handle_ast_nodes(node, exp, vars, pipes);
}

void	abstract_tree_parser(t_node **root, t_parser *parser)
{
	t_vars_i_j	vars;
	t_node		*node;

	vars.i = 0;
	vars.j = 0;
	parser->n_pipes = count_tokens(parser, PIPE);
	parser->n_of_redirections = count_tokens(parser, REDIRECTION);
	node = malloc(sizeof(t_node));
	*root = node;
	if (parser->n_pipes == 0)
		only_one_cmd(parser->exp, node);
	else
		parsing_of_pipes(parser->exp, node, &vars, parser->n_pipes);
	if (parser->n_pipes == 1)
		node->type = IS_A_PIPE;
	parse_red(parser, &node);
	if (parser->n_of_redirections != 0)
		get_cmd_and_file(&node, parser);
}
