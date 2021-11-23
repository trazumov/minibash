#ifndef FUNCTIONS_H
# define FUNCTIONS_H

t_token	*create_tmp_token(void);

//int		ft_strcmp(const char *s1, const char *s2);
//int		init_env(t_minishell *shell, char **envp);
void	ft_signal(int code);
void	on_eof(t_minishell *shell);
void	init_shell(t_minishell *shell);
void	free_data(t_token *a_tokens, t_token *b_tokens);
void	execution(t_minishell *shell, char **envp);
void	main_body(t_minishell *shell, char **envp);

void simple_cmd(char **argv, char **envp);
void free_char_list(char **list);
//void	split_free(char **paths);
void execute_pipe_cmd(t_token *token, char **envp);
void execute_last_cmd(t_token *token, char **envp);
int	open_file_error(t_minishell *shell);
int set_redirection(t_minishell *shell);

int execute_builtin(t_token *token, char **envp);

void	exec_here_doc(t_minishell *shell, t_token *token);
int	get_next_line(int fd, char **line);
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char const *s2);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);

#endif