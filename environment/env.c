/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:58:47 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/11 20:41:07 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @define: Retorna o size da env variable  
 *  
 * @params: 
 * 
 * @return_value:
 * 
 */

char	*cut_string(char *cmd, int start, int end)
{
	char	*ret;
	int		i;
	int		size;

	if (start >= end || end > ft_strlen(cmd))
		exit(4);
	size = end - start;
	ret = malloc(size + 1);
	i = -1;
	while (++i < size)
		ret[i] = cmd[start + i];
	ret[i] = '\0';
	return (ret);
}

char	*rem_from_str(char *cmd, int start, int len)
{
	char	*ret;
	int		i;
	int		x;

	if (start >= ft_strlen(cmd))
		exit(4);
	if (start == 0)
		return (ft_strdup(cmd + len));
	if (len + start >= ft_strlen(cmd))
		return (ft_substr(cmd, start, len));
	ret = malloc(len + 1);
	i = -1;
	while (++i < start)
		ret[i] = cmd[i];
	x = -1;
	while (cmd[start + len] != '\0')
	{
		ret[i] = cmd[start + len + i];
		i++;
	}
	ret[i] = '\0';
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

int	size_rem_env(char *line, int start, bool brackets, int *i)
{
	int	size;

	*i = set_brackets_to_true(line, (*i) + 1, &brackets);
	if (brackets == true)
	{
		size = 2;
		while (line[start++] != '}')
			size++;
		return (size + 1);
	}
	size = 1;
	while (line[start] && !is_space(line[start]) && size++)
		start++;
	return (size - 1);
}

/**
 * 
 * @definition: Replace the env variable in the line to the
 * actual value 
 * 
 * @params: line -> command line
 * 
 * @return_value: line with the environment variables values
 * 
 */

char	*add_value(char *line, int start, char *value)
{
	int		size;
	char	*ret;
	int		i;
	int		x;

	size = ft_strlen(line) + ft_strlen(value);
	ret = malloc(size + 1);
	i = -1;
	while (++i < start)
		ret[i] = line[i];
	i = -1;
	while (value[++i])
		ret[start + i] = value[i];
	if (start + i == size)
	{
		ret[start + i] = '\0';
		return (ret);
	}
	x = -1;
	while (line[++x] != '\0')
		ret[start + i++] = line[x];
	ret[start + i] = '\0';
	free(line);
	return (ret);
}

void	expand_vars(char *line, int pos, int i, bool bracket)
{
	char	*name;
	char	*value;
	int		start;
	int		end;

	start = 0;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			pos = i + 1;
			name = ft_substr(line, pos, size_rem_env(line, pos, bracket, &i));
			value = getenv(name);
			if (value == NULL)
				printf("Didn't found env %s\n", name);
			end = pos + ft_strlen(name);
			pos--;
			line = add_value(rem_from_str(line, pos, end), pos, value);
			i += ft_strlen(value) - 1;
			if (i >= ft_strlen(line))
				break ;
			start = i;
		}
	}
}
