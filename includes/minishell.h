/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:47:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/26 03:00:46 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "tokens.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../Libft/includes/libft.h"

# define SPACES " \n\t\r\a"
# define READ_END 0
# define WRITE_END 1
# define FORKED_CHILD 0

static int	g_error_code = 0;

typedef enum s_error_code
{
	GENERAL_ERROR = 1,
	COMMAND_NOT_FOUND = 127,
}	t_error_code;

typedef enum s_type
{
	IS_A_COMMAND,
	IS_A_PIPE
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

typedef struct s_vars_i_j
{
	int	i;
	int	j;
}	t_vars_i_j;

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

typedef struct s_pipes
{
	int	pfd[2];	
	int	save_fd;
	int	index_for_pipes;
}	t_pipes;

typedef struct s_global
{
	t_parser		parser;
	t_node			*node;
	struct termios	term;
}	t_global;

/******************************/
/*	    Parsing Functions     */
/******************************/

char	*expand_vars(char *line_var, t_lista *lst_envp);
bool	find_quotes(char c, bool *dq, bool *q);
char	**split_quotes(char const *s, int option);
void	get_cmd_and_file(t_node **node, t_parser *parser);
void	file_or_cmd_in_front(t_node *c, t_vars_i_j v, t_parser *p, char *cmd);
bool	command_doesnt_exist(char *cmd, t_node *curr);
bool	check_quotes(t_token token, bool *open_dq, bool *open_q);
int		count_tokens(t_parser *parser, t_token find_token);
char	*eraser_quotes(char *str, bool dq, bool q);
int		not_valid_line(const char *line);
char	*expand_vars(char *line_var, t_lista *lst_envp);
char	*pwd_for_me(void);
char	*if_file_first(t_parser *parser, char *cmd, t_node *node);
char	**return_files(t_parser *parser, char *cmd, int nbr_files);
char	*new_expand_vars(char *exp, t_lista *lst_env);
void	file_or_cmd_in_front(t_node *c, t_vars_i_j v, t_parser *p, char *cmd);
char	*replace_value(char *exp, char *value, t_vars_i_j v, int len);

/******************************/
/*	   Builtins Functions     */
/******************************/

void	list_sort(t_lista *lst);
void	ft_export(char *var, t_lista *envp, t_lista *sort);
void	ft_env(t_lista *lst, char *is_not_null);
int		ft_unset(char *path, t_lista **lst_env, t_lista **lst_sort);
void	list_init(t_listas **listas, char **env);
void	deallocate(t_lista **root);
int		char_check(char *str, char c);
int		copy_check(char *var, t_lista *sort, t_lista *envp);		
int		builtins(t_parser *parser, t_node **node, t_listas *listas, char **cmd);
int		is_builtin(char **line);
void	echo(char **line, int flag_n, t_listas *listas);
char	*eraser_quotes(char *str, bool dq, bool q);

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
t_node	*rec_node_tree_init(char *exp, bool pipe, bool final, t_vars_i_j *l);
bool	is_empty_tree(t_node *node);
void	abstract_tree_parser(t_node **node, t_parser *parser);

/******************************/
/*	     Piping Functions     */
/******************************/

void	ft_exec(t_node *node, int n_pipes, char **env);
int		close_and_save_p(t_pipes *p, int n_pipes);
void	handle_pipes(int p[2], int save_fd, int index_for_pipes, int n_pipes);

/******************************/
/*	     Utils Functions      */
/******************************/

void	free_nodes(t_node **node, t_parser *parser);
int		free_with_return(void *str);

/******************************/
/*	   Builtins Functions     */
/******************************/

#endif
