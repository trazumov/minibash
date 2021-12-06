#include "../../includes/minishell.h"

static int get_argv_size(t_token *token)
{
	int		res;
	t_token	*tmp;

	res = 1; // original name without NULL
	tmp = token;
	while (tmp->next && (tmp->next->type == CMD || tmp->next->type == ARG))
	{
		tmp = tmp->next;
		res++;
	}
	return (res);
}

char **create_argv(t_token *token)
{
	int		size;
	int		i;
	char	**res;
	t_token	*tmp;

	i = 0;
	tmp = token;
	size = get_argv_size(tmp);
	res = malloc(sizeof(char *) * (size + 1));
	while (tmp && (tmp->type == CMD || tmp->type == ARG))
	{
		res[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

int 	execv_cmd(t_minishell *shell, t_token *token)
{
	int res;
	char	**argv;

	argv = create_argv(token);
	res = simple_cmd(argv);
	return res;
}

// нет обработки билтина
void execute_pipe_cmd(t_minishell *shell, t_token *token)
{
	pid_t	parent;
	int		pipefd[2];
	char	**argv;

	argv = create_argv(token);
	pipe(pipefd);
	parent = fork();
	if (parent == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		simple_cmd(argv);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	free_char_list(argv);
}

t_token	*get_prev_token(t_token *token)
{
	t_token	*res;

	if (token->prev == NULL)
		return (NULL);
	else if (token->prev->type == PIPE)
		return (token->prev);
	else
	{
		res = token->prev;
		while (res->prev && res->prev->type != PIPE)
			res = res->prev;
	}
	return (res);
}

void	execute_token(t_minishell *shell, t_token *token)
{
	if (token->type == CMD || token->type == ARG)
		execute_last_cmd(shell, token);
	else if (token->type == BUILTIN)
		execute_builtin(shell, token);
}
