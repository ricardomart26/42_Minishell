/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_cmd_and_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:43:17 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/17 23:31:49 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_string_for_divide(char *cmd, int *start, int *end)
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

char	g_print_tokens[9][20] = {
	"EMPTY",
	"CHAR",
	"SPACE",
	"PIPE",
	"DQ",
	"Q",
	"ENV",
	"REDIRECTION",
};

char	**return_files(t_others *others, char *cmd, int nbr_files)
{
	char	**ret;
	int		i;
	t_vars_x_y	vars;
	t_token	token;

	ret = malloc(sizeof(char *) * (nbr_files + 2));
	if (!ret)
		return (NULL);
	i = 0;
	vars.y = -1;
	vars.x = 0;
	while (cmd[++vars.y])
	{
		c_and_next(&others->c, &others->next, cmd, vars.y);
		token = get_token(others->c, others->next);
		if (vars.y == 0 && token == REDIRECTION)
			continue ;
		else if (token == REDIRECTION)
			ret[i++] = cut_string_for_divide(cmd, &vars.x, &vars.y);
	}
	vars.x++;
	ret[i] = cut_string_for_divide(cmd, &vars.x, &vars.y);
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


// int	find_next_token()
// {
	
// }
void	get_rid_of_spaces(char **arg)
{
	while (is_space(**arg) && **arg != '\0')
		(*arg)++;
}

void	get_rid_of_set(char **arg, char *set)
{
	while ((find_c_in_str(**arg, set) || is_space(**arg)) && **arg != '\0')
		(*arg)++;
}

int	check_if_redirection_first(t_others *others, char *cmd, t_node *node)
{
	t_token	token;
	int		i;
	int		size_until_next_space;
	
	c_and_next(&others->c, &others->next, cmd, 0);
	token = get_token(others->c, others->next);
	i = -1;
	while (token == REDIRECTION)
	{
		if (i == -1)
			node->filename = malloc(sizeof(char *) * 2);
		else			
			node->filename = realloc(node->filename, sizeof(char *) * (i + 2));
		get_rid_of_set(&cmd, "<>");
		size_until_next_space = ft_strlen_c(cmd, ' ');
		node->filename[++i] = ft_substr(cmd, 0, size_until_next_space);
		cmd += size_until_next_space;
		get_rid_of_spaces(&cmd);
		c_and_next(&others->c, &others->next, cmd, 0);
		token = get_token(others->c, others->next);
	}
	node->filename[i + 1] = NULL;
	return (i);
}


t_node	*split_red_and_cmd(t_others *others, t_node *curr, t_token f_token)
{
	t_vars_x_y	vars;
	t_token	token;
	char	*cmd;
	int		option;
	
	cmd = ft_strdup_and_free(&curr->cmd);
	vars.x = 0;
	vars.y = -1;
	option = check_if_redirection_first(others, cmd, curr);
	// if (option != 0)
	// {
	// 	// if (option == ft_strlen(cmd))
	// 	// {
			
	// 	// }
	// 	curr->cmd = ft_substr(cmd, option, ft_strlen(cmd));
	// }
	while (cmd[++vars.y] && option == 0)
	{
		c_and_next(&others->c, &others->next, cmd, vars.y);
		token = get_token(others->c, others->next);
		if (token == f_token)
		{
			vars.x = vars.y;
			curr->cmd = ft_substr(cmd, 0, vars.y);
			break ;
		}
	}
	if (vars.x != 0 && option == 0)
		curr->filename = return_files(others, (cmd + vars.y + 1), curr->n_red);
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

void	divide_cmd_and_file(t_node **node, t_others *others)
{
	t_node	*curr;

	curr = *node;
	if (is_empty_tree(curr))
	{
		curr = split_red_and_cmd(others, curr, REDIRECTION);
		if (curr->cmd == NULL)
			exit(4);
	}
	else
	{
		while (curr->l->end_of_tree != true)
		{
			if (curr->l->n_red != 0)
				curr->l = split_red_and_cmd(others, curr->l, REDIRECTION);
			curr = curr->r;
		}
		if (curr->l->n_red != 0)
			curr->l = split_red_and_cmd(others, curr->l, REDIRECTION);
		if (curr->r->n_red != 0)
			curr->r = split_red_and_cmd(others, curr->r, REDIRECTION);
	}
}
