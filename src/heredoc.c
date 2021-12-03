#include "../includes/minishell.h"

static void	create_tmp_file(t_token *token)
{
	int		in;
	char	*line;

	in = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (in < 0 || read(in, 0, 0) < 0)
	{
		perror("here_doc error");
		exit(EXIT_FAILURE);
	}
	//dup2(0, STDIN);
	ft_putstr_fd("> ", 0);
	while (get_next_line(0, &line))
	{
		if (ft_strncmp(line, token->next->str, ft_strlen(token->next->str) + 1) == 0)
			break ;
		ft_putendl_fd(line, in);
		free(line);
		ft_putstr_fd("> ", 0);
	}
	free(line);
	close(in);
}

void	exec_here_doc(t_minishell *shell, t_token *token)
{
	if (dup2(shell->in, STDIN) == -1)
		perror(shell->message);
	close(shell->in);
	create_tmp_file(token);
	shell->in = dup(STDIN);
	if (shell->in == -1)
		perror(shell->message);
	shell->fd_in = open("here_doc", O_RDONLY);
	if (shell->fd_in < 0 || read(shell->fd_in, 0, 0) < 0)
	{
		perror(shell->message);
		shell->error = TRUE;
		exit(EXIT_FAILURE);
	}
	if (dup2(shell->fd_in, 0) == -1)
		perror(shell->message);
	close(shell->fd_in);
}