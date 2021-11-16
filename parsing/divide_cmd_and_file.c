/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_cmd_and_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 03:43:17 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/16 18:43:05 by rimartin         ###   ########.fr       */
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

char	**return_files(t_parse *ps, char *cmd, int nbr_files)
{
	char	**ret;
	int		i;
	t_limit	l;
	t_token	token;

	ret = malloc(sizeof(char *) * (nbr_files + 2));
	if (!ret)
		return (NULL);
	i = 0;
	l.end = -1;
	l.start = 0;
	while (cmd[++l.end])
	{
		c_and_next(&ps->c, &ps->next, cmd, l.end);
		token = get_token(ps->c, ps->next);
		if (l.end == 0 && token == REDIRECTION)
			continue ;
		else if (token == REDIRECTION)
			ret[i++] = cut_string_for_divide(cmd, &l.start, &l.end);
	}
	l.start++;
	ret[i] = cut_string_for_divide(cmd, &l.start, &l.end);
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

t_node	*split_red_and_cmd(t_parse *st, t_node *curr, t_token f_token)
{
	t_limit	l;
	t_token	token;
	char	*cmd;

	cmd = ft_strdup_and_free(&curr->cmd);
	l.start = 0;
	l.end = -1;
	while (cmd[++l.end])
	{
		c_and_next(&st->c, &st->next, cmd, l.end);
		token = get_token(st->c, st->next);
		if (token == f_token)
		{
			l.start = l.end;
			curr->cmd = ft_substr(cmd, 0, l.end);
			break ;
		}
	}
	if (l.start != 0)
		curr->filename = return_files(st, (cmd + l.end + 1), curr->n_red);
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

void	divide_cmd_and_file(t_node **node, t_parse *st)
{
	t_node	*curr;

	curr = *node;
	if (is_empty_tree(curr))
	{
		curr = split_red_and_cmd(st, curr, REDIRECTION);
		if (curr->cmd == NULL)
			exit(4);
	}
	else
	{
		while (curr->l->end_of_tree != true)
		{
			if (curr->l->n_red != 0)
				curr->l = split_red_and_cmd(st, curr->l, REDIRECTION);
			curr = curr->r;
		}
		if (curr->l->n_red != 0)
			curr->l = split_red_and_cmd(st, curr->l, REDIRECTION);
		if (curr->r->n_red != 0)
			curr->r = split_red_and_cmd(st, curr->r, REDIRECTION);
	}
}
