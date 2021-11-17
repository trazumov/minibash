#ifndef FUNCTIONS_H
# define FUNCTIONS_H

t_token	*create_tmp_token(void);

int		ft_strcmp(const char *s1, const char *s2);
int		init_env(t_minishell *shell, char **envp);
void	ft_signal(int code);
void	on_eof(t_minishell *shell);
void	init_shell(t_minishell *shell);
void	free_data(t_token *a_tokens, t_token *b_tokens);
void	execution(t_minishell *shell, char **envp);
void	main_body(t_minishell *shell, t_token *curr_token, char **envp);

void	parse(t_token **token, char *str);
t_token	*new_tokens(t_token *origin_token);

#endif