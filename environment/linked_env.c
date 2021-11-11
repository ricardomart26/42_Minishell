/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:19:45 by ricardo           #+#    #+#             */
/*   Updated: 2021/11/11 20:40:24 by rimartin         ###   ########.fr       */
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
	int	x;

	i = 0;
	(*curr)->keyword = ft_strndup(env, ft_strlen_c(env, '='));
	(*curr)->value = malloc(ft_strlen_range(env, ft_strlen_c(env, '='), 0) + 1);
	x = -1;
	while (++x < ft_strlen_range(env, ft_strlen_c(env, '='), 0))
		(*curr)->value[x] = env[x + ft_strlen_c(env, '=')];
	(*curr)->value[x] = '\0';
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
		add_values_to_t_env(&curr, env[i]);
		if (env[i + 1])
		{
			curr->next = curr;
			curr = malloc(sizeof(t_env));
		}
	}
	curr->next = NULL;
	return (environment);
}
