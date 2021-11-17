#ifndef TOKENS_H
# define TOKENS_H

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

#endif