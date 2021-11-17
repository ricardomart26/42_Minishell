/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:47:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/17 23:33:42 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include "../Libft/includes/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include "tokens.h"

# define SPACES " \n\t\r\a"
# define READ_END 0
# define WRITE_END 1
# define FORKED_CHILD 0

typedef struct s_node	t_node;

typedef struct s_vars_x_y
{
	int	x;
	int	y;
}	t_vars_x_y;

typedef enum s_type
{
	COMMAND,
	PIPESS
}	t_type;

typedef struct s_split
{
	char	**tab;
	bool	dq;
	bool	q;
}	t_split;

typedef struct s_others
{
	int		n_pipes;
	int		amount_red;
	bool	open_q;
	bool	open_dq;
	int		c;
	int		next;
	char	*exp;
}	t_others;

typedef enum s_red
{
	NOTHING,
	TO_PIPE,
	TO_OUTFILE,
	TO_INFILE,
	TO_APPEND,
	TO_HEREDOC
}	t_red;


struct s_node
{
	t_node	*l;
	t_node	*r;
	char	*cmd;
	char	**filename;
	t_red	*red;
	int		n_red;
	int		fd_h;
	bool	pipe;
	bool	first_cmd;
	bool	end_of_tree;
	bool	has_heredoc;
	t_type	type;
};

typedef struct s_lista
{
	char			*content;
	struct s_lista	*next;
}	t_lista;

typedef struct s_listas
{
	t_lista	*linked_env;
	t_lista	*sort;
}	t_listas;

typedef struct s_global
{
	t_others	ps;
	t_lista		*linked_env;
	t_node		*node;
}	t_global;

/******************************/
/*	   Builtins Functions     */
/******************************/

void		list_sort(t_lista *lst);
int			ft_export(char *var, t_lista *envp, t_lista *sort);
int			ft_env(t_lista *lst);
int			ft_unset(char *path, t_lista *lst_env, t_lista *lst_sort);
void		list_init(t_listas *listas, char **env);
void		deallocate(t_lista **root);
void		list_sort(t_lista *lst);
int			char_check(char *str, char c);
int			copy_check(char *var, t_lista *sort, t_lista *envp);		
int			builtins(t_others *others, t_node **node, char **env, char **cmd);

/******************************/
/*	  Redirection Functions   */
/******************************/

void		check_redirections_on_command(t_node *node);
void		rl_heredoc(t_node *node, char *del);
void		is_heredoc(t_node *node);		
void		do_infile(char *filename);
t_red		check_red(int c, int next);
void		parse_red(t_others *others, t_node **node);
void		do_outfile(char *filename);
void		do_append(char *filename);

/******************************/
/*	    Parsing Functions     */
/******************************/

bool		find_quotes(char c, bool *dq, bool *q);
char		**ft_split_quotes(char const *s);
void		divide_cmd_and_file(t_node **node, t_others *others);
bool		check_quotes(t_token token, bool *open_dq, bool *open_q);
t_token		get_token(int c, int next);
void		c_and_next(int *c, int *next, char *str, int i);
int			count_tokens(t_others *others, t_token find_token);
char		*magic_eraser_quotes(char *str, bool dq, bool q);

/******************************/
/*	      AST Functions       */
/******************************/

void		only_one_cmd(char *exp, t_node *node);
t_node		*rec_node_tree_init(char *exp, bool pipe, bool final, t_vars_x_y *l);
bool		is_empty_tree(t_node *node);
t_node		*abstract_tree_parser(t_node *node, t_others *others);

/******************************/
/*	     Piping Functions     */
/******************************/

void		my_exec(t_node *node, t_others *others, char **env);

/******************************/
/*	     Utils Functions      */
/******************************/

void		free_nodes(t_node **node);

/******************************/
/*	   Builtins Functions     */
/******************************/


#endif
