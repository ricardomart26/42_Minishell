/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:18:36 by jmendes           #+#    #+#             */
/*   Updated: 2021/11/11 14:43:26 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*int	unset(char *path, t_list **list_envp)
{
	t_list *to_remove;
	t_list *current;

	temp = NULL;
	if (ft_strncmp(path, list_envp->content, ft_strlen(path)) == 0)
	{
		temp = list_envp;
		list_envp = list_envp->next;
		ft_lstdelone(temp, free);
		return (0);
	}
	while (ft_strncmp(path, list_envp->content, ft_strlen(path)) != 0)
	{
		temp = list_envp;
		list_envp = list_envp->next;
	}
	temp->next = list_envp->next;
	ft_lstdelone(list_envp, free);
	return (0);
}*/

typedef struct s_lista
{
	char 			*content;
	struct s_lista *next;
} 				t_lista;

int		char_check(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

int		copy_check(char *var, t_lista *sort, t_lista *envp)
{
	int		index;
	t_lista	*current;
	t_lista	*current1;

	current = sort;
	current1 = envp;
	index = char_check(var, '=');
	if (index == -1)
	{
		while (current != NULL)
		{
			if (ft_strncmp(var, current->content, ft_strlen(current->content)) == 0)
			{
				return (-1);
			}
			current = current->next;
		}
	}
	else
	{
		while (current != NULL)
		{
			if (ft_strncmp(var, current->content, index) == 0)
			{
				current->content = ft_strdup(var);
				current1->content = ft_strdup(var);
				return (-1);
			}
			current = current->next;
			current1 = current1->next;
		}
	}
	return (0);
}

void	deallocate(t_lista **root)
{
	t_lista *temp;
	t_lista *current;

	current = *root;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free (temp);
	}
	*root = NULL;
}

void list_sort(t_lista *lst)
{
	t_lista *current;
	t_lista *after;
	char *temp;
	int index;

	index = 0;
	current = lst;
	while (current->next != NULL)
	{
		after = current->next;
		while (after != NULL)
		{
			index = 0;
			if ((unsigned char)current->content[0] > (unsigned char)after->content[0])
			{
				temp = ft_strdup(current->content);
				current->content = ft_strdup(after->content);
				after->content = ft_strdup(temp);
			}
			else if ((unsigned char)current->content[0] == (unsigned char)after->content[0])
			{
				while ((unsigned char)current->content[index] == (unsigned char)after->content[index])
				{
					index++;
					if ((unsigned char)current->content[index] > (unsigned char)after->content[index])
					{
						temp = ft_strdup(current->content);
						current->content = ft_strdup(after->content);
						after->content = ft_strdup(temp);
					}
					else if ((unsigned char)current->content[index] < (unsigned char)after->content[index])
						break;
				}
			}
	
			after = after->next;
		}
		printf("declare -x %s\n", current->content);
		current = current->next;
	}
	printf("declare -x %s\n", current->content);
	//deallocate(lst);
	//free(temp);
	//deallocate(&current);
}

int export(char *var, t_lista *envp, t_lista *sort)
{
	if (var == NULL)
		list_sort(sort);
	else
	{
		if (copy_check(var, sort, envp) == 0)
		{
			ft_lstadd_back((void *)&sort, ft_lstnew((void *)ft_strdup(var)));
			if (char_check(var, '=') != -1)
				ft_lstadd_back((void *)&envp, ft_lstnew((void *)ft_strdup(var)));
		}
	}
	return (0);
}

int	env(t_lista *lst)
{
	t_lista *current;

	current = lst;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_lista *lst_envp;
	t_lista *lst_sort;
	int index;

	index = 0;
	lst_envp = NULL;
	while (envp[index] != NULL)
	{
		ft_lstadd_back((void *)&lst_envp, ft_lstnew((void *)ft_strdup(envp[index])));
		ft_lstadd_back((void *)&lst_sort, ft_lstnew((void *)ft_strdup(envp[index])));
		index++;
	}

	env(lst_envp);
	printf("###############\n");
	export(NULL, lst_envp, lst_sort);
	export("Nva var", lst_envp, lst_sort);
	export("Nva var", lst_envp, lst_sort);
	printf("###############\n");
	export(NULL, lst_envp, lst_sort);
	printf("###############\n");
	env(lst_envp);
	// deallocate(&lst_envp);
	/*t_lista *current = lst_envp;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}*/
return (0);
}
