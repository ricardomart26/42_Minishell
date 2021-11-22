/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_and_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:43:17 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/22 22:30:26 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @definition:
 * 
 * @params:
 * 
 * @return_value:
 * 
 */

char	*get_only_file(char *cmd, int *start, int *end)
{
	char	*ret;
	int		i;
	int		size;

	if (*start >= *end || *end > ft_strlen(cmd))
		exit(4);
	size = *end - *start;
	malloc_guard((void *)&ret, size + 1, sizeof(char));
	i = -1;
	while (++i < size)
		ret[i] = cmd[*start + i];
	ret[i] = '\0';
	while (cmd[(*start) + i] == '<' || cmd[(*start) + i] == '>')
	{
		i++;
		(*end)++;
	}
	*start = *end;
	return (ret);
}

/**
 * 
 * @definition:
 * 
 * @params:
 * 
 * @return_value:
 * 
 */

char	**return_files(t_parser *parser, char *cmd, int nbr_files)
{
	char		**ret;
	int			i;
	t_vars_i_j	vars;
	t_token		token;

	ret = malloc(sizeof(char *) * (nbr_files + 2));
	if (!ret)
		return (NULL);
	i = 0;
	vars.j = -1;
	vars.i = 0;
	while (cmd[++vars.j])
	{
		c_and_next(&parser->c, &parser->next_c, cmd, vars.j);
		token = get_token(parser->c, parser->next_c);
		if (token == REDIRECTION)
			ret[i++] = get_only_file(cmd, &vars.i, &vars.j);
	}
	vars.i++;
	ret[i] = get_only_file(cmd, &vars.i, &vars.j);
	ret[i + 1] = NULL;
	return (ret);
}

/**
 * 
 * @definition: Splits the command and the redirection
 * 
 * @params: st -> geral struct
 * curr -> node advanced in the tree, left if not in the end of tree, and left
 * or right node if in the end of the tree
 * f_token -> token to find
 * 
 * @return_value: Returns the node with the cmd and files separated
 * 
 */

t_node	*split_file_and_cmd(t_parser *parser, t_node *curr)
{
	t_vars_i_j	vars;
	t_token		token;
	char		*cmd;

	cmd = ft_strdup_and_free(&curr->cmd);
	vars.i = 0;
	vars.j = -1;
	cmd = if_file_first(parser, ft_strtrim(cmd, " "), curr);
	if (command_doesnt_exist(cmd, curr))
		return (curr);
	while (cmd[++vars.j])
	{
		c_and_next(&parser->c, &parser->next_c, cmd, vars.j);
		token = get_token(parser->c, parser->next_c);
		if (token == REDIRECTION)
		{
			vars.i = vars.j;
			curr->cmd = ft_substr(cmd, 0, vars.j);
			break ;
		}
	}
	while (find_c_in_str(cmd[vars.j], "<>"))
		vars.j++;
	file_or_cmd_in_front(curr, vars, parser, cmd);
	return (curr);
}

/**
 *
 * @definition: Divide the command and the file (ls -la < file.txt >> file2.txt)
 * It becomes (node->cmd = ls -la) and 
 * (node->red[0] = TO_INFILE and node->filename[0] = file.txt) and
 * (node->red[1] = TO_APPEND and node->filename[1] = file2.txt).
 *
 *
 * @params: node -> Current tree with the commands and files
 * st -> geral struct 
 *
 * @return_value: Add command , files and red to the node struct
 *
 */

void	get_cmd_and_file(t_node **node, t_parser *parser)
{
	t_node	*curr;

	curr = *node;
	if (is_empty_tree(curr))
		curr = split_file_and_cmd(parser, curr);
	else
	{
		while (curr->l->end_of_tree != true)
		{
			if (curr->l->n_red != 0)
				curr->l = split_file_and_cmd(parser, curr->l);
			curr = curr->r;
		}
		if (curr->l->n_red != 0)
			curr->l = split_file_and_cmd(parser, curr->l);
		if (curr->r->n_red != 0)
			curr->r = split_file_and_cmd(parser, curr->r);
	}
}
