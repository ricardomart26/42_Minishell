/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:19:45 by ricardo           #+#    #+#             */
/*   Updated: 2021/11/08 01:27:46 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @definition: add the keyword (USER/HOME/...) and value of the keyword
 * (value assign to the env var) to t_env linked list 
 * 
 * @params: 
 * curr -> t_env linked list that is 
 * env -> Environment variables
 * 
 * @return_value: void
 * 
 */

void	add_values_to_t_env(t_env **curr, char *env)
{
	int	i;
	int	size;
	int	x;
	int	save_i;

	i = 0;
	size = 0;
	while (env[i] && env[i] != '=')
		i++;
	(*curr)->keyword = malloc(i + 1);
	x = -1;
	while (++x < i)
		(*curr)->keyword[x] = env[x];
	save_i = i + 1;
	while (env[++i])
		size++;
	(*curr)->value = malloc(size + 1);
	x = -1;
	while (++x < size)
		(*curr)->value[x] = env[save_i++];
}

/**
 * @definition: Convert all environment variables to a linked list,
 * split after the first equal sign
 * 
 * @params:
 * env -> Environment variable
 * 
 * @return_value: Returns env in a linked list
 */

t_env	*env_to_linked_list(char **env)
{
	t_env	*environment;
	int		i;
	t_env	*curr;

	environment = malloc(sizeof(t_env));
	curr = environment;
	i = -1;
	while (env[++i])
	{
		add_values_to_t_env(&environment, env[i]);
		if (env[i + 1])
		{
			curr->next = curr;
			curr = malloc(sizeof(t_env));
		}
	}
	curr->next = NULL;
	return (environment);
}
