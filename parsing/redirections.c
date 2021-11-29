/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 02:09:17 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/29 20:11:07 by rimartin         ###   ########.fr       */
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

	size = *end - *start;
	malloc_guard((void *)&ret, size + 1, sizeof(char));
	i = -1;
	while (++i < size)
		ret[i] = cmd[*start + i];
	ret[i] = '\0';
	while ((cmd[(*start) + i] == '<' || cmd[(*start) + i] == '>') && i++)
		(*end)++;
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

char	**return_files(char *cmd, int nbr_files, int i, int j)
{
	char	**ret;
	int		k;

	ret = malloc(sizeof(char *) * (nbr_files + 2));
	if (!ret)
		return (NULL);
	k = 0;
	while (cmd[++j])
		if (get_token(cmd + j) == REDIRECTION)
			ret[k++] = get_only_file(cmd, &i, &j);
	i++;
	ret[k] = get_only_file(cmd, &i, &j);
	ret[k + 1] = NULL;
	return (ret);
}

bool	command_doesnt_exist(char *cmd, t_node *curr)
{
	while (*cmd == ' ')
		cmd++;
	if (ft_strlen(cmd) == 0)
	{
		curr->cmd = NULL;
		return (true);
	}
	return (false);
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

void	split_file_and_cmd(t_node *curr, int i, int j)
{
	char		*cmd;

	cmd = ft_strdup_and_free(&curr->cmd);
	cmd = if_file_first(ft_strtrim(cmd, " "), curr);
	if (command_doesnt_exist(cmd, curr))
		return ;
	while (cmd[++j])
	{
		if (get_token(cmd + j) == REDIRECTION)
		{
			i = j;
			curr->cmd = ft_substr(cmd, 0, j);
			break ;
		}
	}
	while (find_c_in_str(cmd[j], "<>"))
		j++;
	if (i != 0)
		curr->filename = return_files((cmd + j), curr->n_red, 0, -1);
	else
		curr->cmd = ft_substr(cmd, 0, j);
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

void	get_red(t_node *curr, char *cmd, bool open_dq, bool open_q)
{
	int		pos;
	int		n_red;

	pos = -1;
	n_red = 0;
	malloc_guard((void **)&curr->red, 1, sizeof(t_red));
	while (cmd[++pos])
	{
		check_quotes(get_token(cmd + pos), &open_dq, &open_q);
		if (get_token(cmd + pos) == REDIRECTION && (!open_dq && !open_q))
		{
			curr->red[n_red++] = check_red(cmd + pos);
			curr->red = realloc(curr->red, (n_red + 1) * sizeof(t_red));
			if (curr->red[n_red - 1] == TO_HEREDOC
				|| curr->red[n_red - 1] == TO_APPEND)
				pos++;
		}
	}
	curr->red[n_red] = NOTHING;
	curr->n_red = n_red;
	split_file_and_cmd(curr, 0, -1);
}
