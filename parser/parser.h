#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
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

void	ft_echo(t_token *token);
void	ft_env(void);
int		ft_pwd(void);
int		ft_exit(t_token *token);
int		ft_export(t_token *token);
void	ft_unset(t_token *token);
int		ft_cd(t_token *token);
int		ft_is_numeric(char *str);
char	**malloc_environ(void);
int		get_env_size(char **arr);
int		ft_strcmp(const char *s1, const char *s2);
int		print_export_or_unset_error(char *str, int type);
char	**realloc_environ(int diff, char *str);
void	handle_negative_diff(char **arr, char *str, int size);

#endif