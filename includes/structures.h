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

typedef struct s_minishell
{
	t_pid_t	*childs;
	int		built_ret;
	char	*message;
	int		exit;
	int		fds[100][2]; // file descriptors
	int		ret; // возвращаемое значение
	int		in; // сохраненное значение для перезаписи
	int		out; // сохраненное значение для перезаписи
	int		fd_out; // текущий файлдескриптор, depricated
	int		fd_in; // текущий файлдескриптор, depricated
	int		save_history; // сохранять истоирю или нет
	int		wait_s; // сколько wait вызывать
	t_token	*tokens;
}	t_minishell;

#endif