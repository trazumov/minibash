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

//parser
char	*parse(t_token **token, char *str);
void	preparser(char *str, int *sep_ct);
int		check_leading_pipe(char *str, int *sep_ct);
int		ft_isspace(int c);
void	print_error(char *str);
int		ft_issep(int c);
int		handle_sep(char *str, int i, int *sep_ct);
int		handle_pipe(char *str, int i, int *sep_ct);
int		handle_redirection(char *str, int i, int *sep_ct);
char	*parser(char *str, char **array, int token_ct);
char	*handle_quotes(char *str, int *start);
char	*handle_double_quotes(char *str, int *start);
void	remove_quotes(char *str, int start, int end);
char	*handle_bucks(char *str, int *start);
char	*remove_invalid_var_name(char *str, char *var_name, int *start);
void	free_intermediate_strings(char *t, char *p_1, char *p_2, char *var);

//tokens
void	create_tokens(t_token **token, char **array, int token_ct);
void	ft_add_token(t_token **lst, t_token *new);
t_token	*ft_new_token(void);
t_token	*ft_last_token(t_token *lst);
void	assign_type(t_token *token, char *str);

//builtins
int		ft_echo(t_token *token);
int		ft_env(void);
int		ft_pwd(void);
int		ft_exit(t_token *token);
int		ft_export(t_token *token);
int		ft_unset(t_token *token);
int		ft_cd(t_token *token);

//builtins_utils
int		is_arg_numeric(char *str);
void	insertion_sort(char **arr, int size);
void	print_sorted_env(void);
int		check_var_name(char *str);
int		print_export_or_unset_error(char *str, int type);
char	*get_var_name(char *str);
void	add_var(char *var_name, char *str);
int		is_name_valid(char *str);
int		print_cd_error(char *str, int type);
int		change_dir_to_home_or_oldpwd(char *var);
void	update_oldpwd(char *oldpwd);

//environ
char	**malloc_environ(void);
int		get_env_size(char **arr);
char	**realloc_environ(int diff, char *str);
void	handle_negative_diff(char **arr, char *str, int size);

//utils
int		ft_strcmp(const char *s1, const char *s2);

#endif