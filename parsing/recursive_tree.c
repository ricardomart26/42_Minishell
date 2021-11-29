/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:48:39 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/29 20:37:09 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*rec_node_tree_init(char *exp, bool final, t_vars_i_j *vars)
{
	t_node	*node;
	int		i;
	int		size;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = IS_A_COMMAND;
	size = vars->j - vars->i;
	node->end_of_tree = false;
	if (final)
		node->end_of_tree = true;
	node->cmd = malloc(size + 1);
	i = -1;
	while (++i < size)
		node->cmd[i] = exp[vars->i + i];
	node->cmd[i] = '\0';
	get_red(node, node->cmd, false, false);
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
	if (pipes > 2)
	{
		temp->l = rec_node_tree_init(exp, false, vars);
		temp->r = malloc(sizeof(t_node));
		temp->r->l = NULL;
		temp->r->end_of_tree = false;
		temp->r->type = IS_A_PIPE;
	}
	else if (pipes == 2)
		temp->l = rec_node_tree_init(exp, true, vars);
	else
		temp->r = rec_node_tree_init(exp, true, vars);
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
	bool	open_dq;
	bool	open_q;

	open_dq = false;
	open_q = false;
	if (pipes == 0)
		return (only_one_cmd(exp, node));
	while (exp[vars->j])
	{
		check_quotes(get_token(exp + vars->j), &open_dq, &open_q);
		if (get_token(exp + vars->j) == PIPE && (!open_dq && !open_q))
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

void	count_pipes(char *exp, int *n_pipes)
{
	int		i;
	bool	open_dq;
	bool	open_q;
	t_token	token;

	open_dq = false;
	open_q = false;
	i = -1;
	while (exp[++i])
	{
		token = get_token(exp + i);
		check_quotes(token, &open_dq, &open_q);
		if (token == PIPE && (!open_dq && !open_q))
			(*n_pipes)++;
	}
}

void	abstract_tree_parser(t_node **root,
			char **exp, int *n_pipes, t_lista *linked_env)
{
	t_vars_i_j	vars;
	t_node		*node;

	vars.i = 0;
	vars.j = 0;
	new_expand_vars(exp, linked_env);
	count_pipes(*exp, n_pipes);
	node = malloc(sizeof(t_node));
	*root = node;
	if (*n_pipes == 0)
		parsing_of_pipes(*exp, node, &vars, *n_pipes);
	else
		parsing_of_pipes(*exp, node, &vars, (*n_pipes) + 1);
	if (*n_pipes == 1)
		node->type = IS_A_PIPE;
}
