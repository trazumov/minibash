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

static char **create_argv(t_token *token)
{
	int		size;
	int		i;
	char	**res;
	t_token	*tmp;

	i = 0;
	tmp = token;
	size = get_argv_size(tmp);
	res = malloc(sizeof(char *) * size + 1); // + NULL
	while (tmp && (tmp->type == CMD || tmp->type == ARG))
	{
		res[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void 	execute_last_cmd(t_minishell *shell, t_token *token)
{
	pid_t	parent;
	char	**argv;

	argv = create_argv(token);
	parent = fork();
	if (parent)
	{
		waitpid(parent, &shell->question, 0);
		free_char_list(argv);
	}
	else
		simple_cmd(argv);
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
	if (parent)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		waitpid(parent, &shell->question, 0);
		free_char_list(argv);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		if (token->type == CMD)
			simple_cmd(argv);
	}
}
