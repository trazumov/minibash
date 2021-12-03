#include "../../includes/minishell.h"

void	init_shell(t_minishell *shell)
{
	shell->message = ft_strdup("minishell$ ");
	shell->exit = FALSE;
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->wait_s = 0;
	shell->save_history = TRUE;
	shell->childs = NULL;
	shell->error = FALSE;
}
/*
// 0 OK 1 break 2 continue
static int main_cycle(t_minishell *shell, char **input, t_token **parsed_tokens)
{
	init_shell(shell);
	if (*input)
		free(*input);
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
	
	pre_init(&shell, arr);
	cycle = main_cycle(&shell, &input, &parsed_tokens);
	while (shell.exit != TRUE)
	{
		cycle = main_cycle(&shell, &input, &parsed_tokens);
		if (cycle == 1)
			break ;
		if (cycle == 2)
			continue ;
	}
	free(__environ);
	__environ = arr;
	return (0);
}

int main(void)
{
	t_minishell	shell;
	t_token		*parsed_tokens = NULL;
	char		*input = NULL;
	char		**arr = NULL;
	int			first_call;
	
	input = readline("minishell$ ");
	first_call = TRUE;
	pre_init(&shell, arr);
	while (shell.exit != TRUE)
	{
		init_shell(&shell);
		if (input && !first_call)
			free(input);
		if (!first_call)
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
		first_call = FALSE;
	}
	free(__environ);
	__environ = arr;
	return (0);
}
*/