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
	else
		add_history("");
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

static int ctrl_d(t_minishell *shell, char *input)
{
	if (input == NULL)
	{
		on_eof(shell);
		return (TRUE);
	}
	return (FALSE);
}

int main(void)
{
	t_minishell	shell;
	t_token		*parsed_tokens = NULL;
	char		*input = NULL;
	char		**arr = NULL;
	
	pre_init(&shell, arr);
	while (shell.exit != TRUE)
	{
		init_shell(&shell);
		if (input)
			free(input);
		input = readline(shell.message);
		if (ctrl_d(&shell, input))
			break ;
		update_history(input);
		input = parse(&parsed_tokens, input, shell);
		if (input == NULL)
			continue ;
		post_init_tokens(parsed_tokens); // вывести в parse и тогда будет 25 строчек
		shell.tokens = parsed_tokens;
		execution(&shell);
		free_tokens(&parsed_tokens);
	}
	free(__environ);
	__environ = arr;
	return (0);
}