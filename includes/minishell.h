#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

# define TYPE_CMD 0
# define TYPE_BUILTIN 1
# define TYPE_PIPE 2
# define TYPE_RED_INP 3
# define TYPE_RED_OUT 4

int			g_signal;

typedef struct s_env
{
	char	*str;
	struct	s_env *next;
}	t_env;

typedef struct s_token
{
	int	type;
	struct s_token *next;
}	t_token;

typedef struct s_minishell
{
	int		exit;
	char	*message;
	t_env	*env;
	t_token	*tokens;
}	t_minishell;

int		ft_strcmp(const char *s1, const char *s2);
void	parser(t_minishell *shell, char *input);
int		init_env(t_minishell *shell, char **envp);
void	ft_signal(int code);
void	on_eof(t_minishell *shell);
void	init_shell(t_minishell *shell);
void	free_data(t_minishell *shell);
void	execution(t_minishell *shell);
t_token *create_tmp_token(void);

 #endif