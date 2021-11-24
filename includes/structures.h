#ifndef STRUCTURES_H
# define STRUCTURES_H

int		g_return;

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
	int				skip;
}	t_token;

typedef struct s_minishell
{
	int		question;
	char	*message;
	int		exit;
	int		ret;
	int		in;
	int		out;
	int		fd_out;
	int		fd_in;
	int		save_history;
	t_env	*env;
	t_token	*tokens;
}	t_minishell;

#endif