/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:47:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/12/02 20:16:05 by rimartin         ###   ########.fr       */
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
	bool			end_of_tree;
	bool			has_heredoc;
	t_type			type;
}	t_node;

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
	t_node			*node;
	struct termios	term;
	int				error_code;
	int				inside_command;
	char			*exp;
	int				n_pipes;
}	t_global;

t_global	g_gl;

/******************************/
/*	    Parsing Functions     */
/******************************/

bool		find_quotes(char c, bool *dq, bool *q);
char		**split_quotes(char const *s, int option);
void		get_cmd_and_file(t_node **node);
bool		command_doesnt_exist(char *cmd, t_node *curr);
bool		check_quotes(t_token token, bool *open_dq, bool *open_q);
void		count_pipes(char *exp, int *n_of_pipes);
int			not_valid_line(const char *line);
char		*if_file_first(char *cmd, t_node *node);
void		new_expand_vars(char **exp, t_lista *lst_env);
void		file_or_cmd_in_front(t_node *c, t_vars_i_j v, char *cmd);
char		*replace_value(char *exp, char *value, t_vars_i_j v, int len);
char		*eraser_quotes(char *str, bool dq, bool q);
void		get_red(t_node *curr, char *cmd, bool open_dq, bool open_q);

/******************************/
/*	   Builtins Functions     */
/******************************/

void		list_sort(t_lista *lst);
void		ft_export(char *var, t_lista *envp, t_lista *sort);
void		ft_env(t_lista *lst, char *is_not_null);
t_listas	*ft_unset(char *path, t_listas *listas);
void		list_init(t_listas **listas, char **env);
int			char_check(char *str, char c);
int			copy_check(char *var, t_lista *sort, t_lista *envp);		
int			builtins(t_node *node, t_listas *listas, char **cmd);
int			is_builtin(char **line);
void		echo(char **line, int flag_n, t_listas *listas);

/******************************/
/*	  Redirection Functions   */
/******************************/

void		check_redirections_on_command(t_node *node);
void		rl_heredoc(t_node *node, char *del);
void		seek_for_heredoc(t_node *node);
void		heredoc_redirection_and_unlink_file(void);
t_red		check_red(char *str);

/******************************/
/*	      AST Functions       */
/******************************/

void		only_one_cmd(char *exp, t_node *node);
bool		is_empty_tree(t_node *node);
void		abstract_tree_parser(t_node **node, char **exp,
				int *n_pipes, t_lista *linked_env);

/******************************/
/*	     Piping Functions     */
/******************************/

void		ft_exec(t_node *node, int n_pipes, char **env);
int			close_and_save_p(t_pipes *p, int n_pipes);
void		handle_pipes(int p[2], int save_fd,
				int index_for_pipes, int n_pipes);

/******************************/
/*	     Utils Functions      */
/******************************/

void		free_nodes(t_node *node, char **exp);
int			free_with_return(void *str);
int			free_dp(char **dp);

/******************************/
/*	   Signals Functions     */
/******************************/

void		sig_int(int sig);

#endif
