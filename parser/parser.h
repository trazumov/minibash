#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CMD 0
# define ARG 1
# define BUILTIN 2
# define PIPE 3
# define REDIR_OUT 4
# define REDIR_OUT_2 5
# define REDIR_IN 6
# define REDIR_HEREDOC 7

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_minishell
{
	t_env		*env;
	t_token		*token;
	int			return_value;
	int			fd_in;
	int			fd_out;
}				t_minishell;

#endif