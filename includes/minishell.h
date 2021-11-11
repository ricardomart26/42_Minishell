/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:47:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/11/11 18:26:45 by rimartin         ###   ########.fr       */
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

# define SPACES " \n\t\r\a"
# define READ_END 0
# define WRITE_END 1
# define FORKED_CHILD 0

typedef struct s_node	t_node;

typedef struct s_limit
{
	int	start;
	int	end;
}	t_limit;

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

typedef struct s_parse // Parsing
{
	int		n_pipes;
	int		amount_red;
	bool	open_q;
	bool	open_dq;
	int		c;
	int		next;
	int		start;
	int		end;
	char	*exp;
	char	**env;
}	t_parse;

typedef enum s_red
{
	NOTHING,
	TO_PIPE,
	TO_OUTFILE,
	TO_INFILE,
	TO_APPEND,
	TO_HEREDOC
}	t_red;

typedef enum s_token
{
	EMPTY,
	CHAR,
	SPACE,
	PIPE,
	DQ,
	Q,
	ENV,
	REDIRECTION
}	t_token;

struct s_node
{
	t_node	*l;
	t_node	*r;
	char	*cmd;
	char	**filename;
	t_red	*red;
	int		n_red;
	bool	pipe;
	bool	first_cmd;
	bool	end_of_tree;
	t_type	type;
};

typedef struct s_env
{
	char			*keyword;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_context
{
	int	fd[2];
	int	fd_close;
}	t_context;

typedef struct s_global
{
	t_parse	ps;
	t_env	*linked_env;
	t_node	*node;
}	t_global;

int		exec_node(t_node *node, t_context *ctx);
int		count_tokens(t_parse *st, t_token find_token);
bool	is_empty_tree(t_node *node);
bool	find_c_in_str(int c, char *str);
bool	check_quotes(t_token token, bool *open_dq, bool *open_q);
t_token	get_token(int c, int next);
t_red	check_red(int c, int next);
void	parse_exp_pipes(t_parse *st, t_node **node);
void	parse_red(t_parse *st, t_node **node);
void	c_and_next(int *c, int *next, char *str, int i);
void	divide_cmd_and_file(t_node **node, t_parse *st);
void	free_nodes(t_node *node, t_node *old);
char	*cut_string(char *cmd, int start, int end);
t_env	*env_to_linked_list(char **env);
void	expand_vars(char *line, int pos, int i, bool brackets);
char	*cut_string_with_red(char *cmd, int *start, int *end);
char	*heredoc(char *del);
char	*do_infile(char *filename, int fd);
char	*do_outfile(char *filename, int fd);
char	*executor(t_node *node, t_parse st, char **env, int n);
char	*do_append(char *filename, int fd);
void	rl_heredoc(char *del);
int		builtins(t_parse *st, t_env **env, t_node **node);
char	**ft_split_quotes(char const *s, char c);
int		norm_helper(t_split *sp, char const *s, int *i, int *counter);
t_limit	norm_helper2(t_split *sp, char const *s, t_limit l, int *k);
int		exit_builtin(t_parse *st, t_env **env, t_node **node);
bool	check_quotes_split(const char	*str, bool *dq, bool *q, int i);
int		free_node(t_node **node);
void	ft_lstclear_env(t_env **lst, void (*del)(void *));
int		set_brackets_to_true(char *line, int i, bool *brackets);

void	rec_parse_pipes(char *exp, t_node *node, t_limit *l, int pipes);
void	rec_pipe_parser(t_node *node, char *exp, t_limit *l, int pipes);
t_node	*rec_node_tree_init(char *exp, bool pipe, bool final, t_limit *l);
t_parse	*singleton_ps(t_parse *ps);
t_env	*singleton_env(t_env *link);
void	exec(t_node *node);
t_node	*abstract_tree_parser(t_node *node, t_parse *st);
void	only_one_cmd(char *exp, t_node *node);
void	my_exec(t_node *node, t_parse *ps, char **env);

#endif