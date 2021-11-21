/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:34:44 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/21 22:25:37 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// int	check_if_token_next_to_each_other(char **line)
// {
// 	int	i;
// 	int	save_i;
	
// 	i = -1;
// 	while (line[++i])
// 	{
// 		while (line[i])
// 		    if (line[i] == '|')		
// 	}
// 	return (0);
// }

int return_error(char *error, char error_char)
{
    printf("%s", error);
    if (error_char)
        printf("%c\n", error_char);
    return (-1);
}

int repeated_redirections(char **split_line)
{
    t_vars_x_y  vars;
    int         error_code;

    vars.x = -1;
    error_code = 0;
    printf("Entrou?\n");
    while (split_line[++vars.x] && !error_code)
    {
        printf("split line %s\n", split_line[++vars.x]);
    	if (find_c_in_str(split_line[vars.x][0], "<>"))
        {
            if (split_line[vars.x + 1] == NULL || find_c_in_str(split_line[vars.x][0], "<>"))
                return (return_error("syntax error near unexpected token ", split_line[vars.x][0]));
            if (split_line[vars.x][1] == '\0')
                continue ;
            else if (find_c_in_str(split_line[vars.x][0], "<>") && !error_code)
                return (return_error("syntax error near unexpected token ", split_line[vars.x][0]));
        }
    }
    return (0);
}

int repeated_pipes(char **split_line)
{
    t_vars_x_y  vars;
    int         error_code;

    error_code = 0;
    printf("Entrou?\n");
    if (split_line[0][0] == '|')
        error_code = return_error("syntax error near unexpected token ", '|');
    vars.x = -1;
    while (split_line[++vars.x] && !error_code)
    {
    	if (split_line[vars.x][0] == '|')
        {
            if (split_line[vars.x + 1] == NULL || split_line[vars.x + 1][0] == '|')
                return(return_error("syntax error near unexpected token ", '|'));
            if (split_line[vars.x][1] == '\0')
                continue ;
            else if (split_line[vars.x][1] == '|' && !error_code)
                return (return_error("syntax error near unexpected token ", '|'));
        }
    }
    return (0);
}

int not_valid_line(const char *line)
{
    char    **split_line;
    
    split_line = ft_split_quotes(line, 0);
    // print_dp((void *)split_line, 1, 0);
    if (repeated_pipes(split_line))
        return (258);
    else if (repeated_redirections(split_line))
        return (258);
	return (0);
}