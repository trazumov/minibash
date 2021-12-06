#ifndef FUNCTIONS_H
# define FUNCTIONS_H

void	ft_signal(int code);
void	on_eof(t_minishell *shell);
void	init_shell(t_minishell *shell);
void	free_data(t_token *a_tokens, t_token *b_tokens);
void	execution(t_minishell *shell);

int simple_cmd(char **argv);
int		imple_cmd(char **argv);
void	free_char_list(char **list);
void	execute_pipe_cmd(t_minishell *shell, t_token *token);
void 	execute_last_cmd(t_minishell *shell, t_token *token);
int		open_file_error(t_minishell *shell);
int		set_redirection(t_minishell *shell);

int		execute_builtin(t_minishell *shell, t_token *token);
t_token	*get_prev_input(t_token *token);

void	exec_here_doc(t_minishell *shell, t_token *token);
int		redirect_heredoc(t_minishell *shell, t_token *token, int *new_input);
int		get_next_line(int fd, char **line);
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char const *s2);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);

void execute_token(t_minishell *shell, t_token *token);
int 	execv_cmd(t_minishell *shell, t_token *token);
t_token *get_prev_token(t_token *token);

void	free_tokens(t_token **token);
void	execute_pipe(t_minishell *shell, t_token *token, int *curr_pipe);

int	redirect_out(t_minishell *shell, t_token *token, int *new_output);

void first_pipe(t_minishell *shell, t_token *token, int fd);
void mid_pipe(t_minishell *shell, t_token *token, int fd);
void last_pipe(t_minishell *shell, t_token *token, int fd);
void the_only_pipe(t_minishell *shell, t_token *token, int fd);

void	struct_pid_clear(t_pid_t **head);
void	struct_pid_add(t_pid_t **head, t_pid_t *new);
t_pid_t	*struct_pid_new(pid_t value);
int ctrl_d(t_minishell *shell, char *input);
void	close_fd_save(int fd);
void	handle_return_value(int *return_value);
char **create_argv(t_token *token);

#endif