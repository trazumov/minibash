#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_env
{
	char	*str;
	struct	s_env *next;
}	t_env;

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_minishell
{
	int		exit;
	char	*message;
	int		pipin;
	int		pipout;
	int		pid;
	int		parent;
	int		ret;
	int		in;
	int		out;
	t_env	*env;
	t_token	*tokens;
}	t_minishell;

#endif