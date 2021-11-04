#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

# define TYPE_COMMAND 0

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
}	t_minishell;

int		ft_strcmp(const char *s1, const char *s2);
void	parser(t_minishell *shell, char *input);
int		init_env(t_minishell *shell, char **envp);
void	ft_signal(int code);
void	on_eof(t_minishell *shell);
void	init_shell(t_minishell *shell);
void	free_data(t_minishell *shell);

 #endif