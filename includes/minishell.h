/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:47:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/20 20:38:54 by rimartin         ###   ########.fr       */
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

typedef enum s_red
{
	NOTHING,
	TO_OUTFILE,
	TO_INFILE,
	TO_APPEND,
	TO_HEREDOC
}	t_red;

typedef struct s_node
{
	struct s_node	*l;
	struct s_node	*r;
	char			*cmd;
	char			**filename;
	t_red			*red;
	int				n_red;
	bool			pipe;
	bool			first_cmd;
	bool			end_of_tree;
	bool			has_heredoc;
	t_type			type;
}	t_node;

typedef struct s_parser
{
	int		n_pipes;
	int		n_of_redirections;
	bool	open_q;
	bool	open_dq;
	int		c;
	int		next_c;
	char	*exp;
}	t_parser;

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
	t_parser	parser;
	t_node		*node;
}	t_global;

/******************************/
/*	    Parsing Functions     */
/******************************/

char    *expand_vars(char *line_var, t_lista *lst_envp);

bool	find_quotes(char c, bool *dq, bool *q);
char	**ft_split_quotes(char const *s, int option);
void	divide_cmd_and_file(t_node **node, t_parser *parser);
bool	check_quotes(t_token token, bool *open_dq, bool *open_q);
t_token	get_token(int c, int next);
void	c_and_next(int *c, int *next, char *str, int i);
int		count_tokens(t_parser *parser, t_token find_token);
char	*magic_eraser_quotes(char *str, bool dq, bool q);
char	*check_if_redirection_first(t_parser *parser, char *cmd, t_node *node);

/******************************/
/*	   Builtins Functions     */
/******************************/

void	list_sort(t_lista *lst);
int		ft_export(char *var, t_lista *envp, t_lista *sort);
int		ft_env(t_lista *lst);
int		ft_unset(char *path, t_lista *lst_env, t_lista *lst_sort);
void	list_init(t_listas **listas, char **env);
void	deallocate(t_lista **root);
int		char_check(char *str, char c);
int		copy_check(char *var, t_lista *sort, t_lista *envp);		
int		builtins(char *exp, t_node **node, t_listas *listas, char **cmd);
int		is_builtin(char **line);
int		echo(char **line, int flag_n, int error_code, t_listas *listas);

/******************************/
/*	  Redirection Functions   */
/******************************/

void	check_redirections_on_command(t_node *node);
void	rl_heredoc(t_node *node, char *del);
void	seek_for_heredoc(t_node *node);
void	heredoc_redirection_and_unlink_file(void);
void	do_infile(char *filename);
t_red	check_red(int c, int next);
void	parse_red(t_parser *parser, t_node **node);
void	do_outfile(char *filename);
void	do_append(char *filename);

/******************************/
/*	      AST Functions       */
/******************************/

void	only_one_cmd(char *exp, t_node *node);
t_node	*rec_node_tree_init(char *exp, bool pipe, bool final, t_vars_x_y *l);
bool	is_empty_tree(t_node *node);
t_node	*abstract_tree_parser(t_node *node, t_parser *parser);

/******************************/
/*	     Piping Functions     */
/******************************/

void	my_exec(t_node *node, int n_pipes, char **env);

/******************************/
/*	     Utils Functions      */
/******************************/

void	free_nodes(t_node **node);

/******************************/
/*	   Builtins Functions     */
/******************************/

#endif
