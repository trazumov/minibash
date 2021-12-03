#include "../includes/minishell.h"

static void post_init_tokens(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		tmp->skip = FALSE;
		if (tmp->type == CMD && ft_strcmp(tmp->str, "") == 0)
			tmp->skip = TRUE;
		tmp = tmp->next;
	}
}

static void update_history(char *input)
{
	int	onlyspaces;
	int	i;

	i = 0;
	onlyspaces = TRUE;
	while (input[i])
	{
		if (input[i] != ' ')
		{
			onlyspaces = FALSE;
			break ;
		}
		i++;
	}
	if (!onlyspaces)
		add_history(input);
}

static void pre_init(t_minishell *shell, char **arr)
{
	arr = __environ;
	__environ = malloc_environ();
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	g_is_executed = FALSE;
	shell->exit = FALSE;
	shell->ret = 0;
}

static int main_cycle(t_minishell *shell, char **input, t_token **parsed_tokens, int first_call)
{
	init_shell(shell);
	if (*input && !first_call)
		free(*input);
	if (!first_call)
		*input = readline(shell->message);
	if (ctrl_d(shell, *input))
		return (1);
	update_history(*input);
	*input = parse(parsed_tokens, *input, *shell);
	if (*input == NULL)
		return (2);
	post_init_tokens(*parsed_tokens); // вывести в parse и тогда будет 25 строчек
	shell->tokens = *parsed_tokens;
	execution(shell);
	free_tokens(parsed_tokens);
	return (0);
}

int main(void)
{
	t_minishell	shell;
	t_token		*parsed_tokens = NULL;
	char		*input = NULL;
	char		**arr = NULL;
	int			cycle;
	
	input = readline("minishell$ ");
	pre_init(&shell, arr);
	cycle = main_cycle(&shell, &input, &parsed_tokens, TRUE);
	while (shell.exit != TRUE)
	{
		cycle = main_cycle(&shell, &input, &parsed_tokens, FALSE);
		if (cycle == 1)
			break ;
		if (cycle == 2)
			continue ;
	}
	free(__environ);
	__environ = arr;
	return (shell.ret);
}