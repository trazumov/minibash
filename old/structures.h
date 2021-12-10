#ifndef STRUCTURES_H
# define STRUCTURES_H

int		g_is_executed;

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

typedef struct s_pid_t
{
	pid_t			pid;
	struct s_pid_t	*next;
}	t_pid_t;

typedef struct	s_parser
{
	int			i;
	int			j;
	int			last_space;
}				t_parser;

typedef struct s_minishell
{
	t_pid_t	*childs;
	char	*message;
	int		exit;
	int		fds[100][2]; // file descriptors
	int		ret;
	int		error;
	int		in;
	int		out;
	int		fd_out;
	int		fd_in;
	int		save_history; // сохранять истоирю или нет
	t_token	*tokens;
}	t_minishell;

#endif