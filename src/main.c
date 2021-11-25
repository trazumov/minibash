#include "../includes/minishell.h"

static void	free_tokens(t_token **token)
{
	while ((*token)->next != NULL)
		(*token) = (*token)->next;
	while ((*token)->prev != NULL)
	{
		(*token) = (*token)->prev;
		free((*token)->next->str);
		(*token)->next->str = NULL;
		free((*token)->next);
		(*token)->next = NULL;
	}
	free((*token)->str);
	(*token)->str = NULL;
	free(*token);
	*token = NULL;
}

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

int main(void)
{
	t_minishell	shell;
	t_token		*parsed_tokens = NULL;
	char		*input = NULL;
	char		**arr = NULL;
	
	arr = __environ;
	__environ = malloc_environ();
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	shell.exit = FALSE;
	shell.question = 0;
	while (shell.exit != TRUE)
	{
		init_shell(&shell);
		if (input)
			free(input);
		input = readline(shell.message);
		if (input == NULL)
		{
			on_eof(&shell);
			break ;
		}
		if (input[0] == '\0')
			continue ;
		input = parse(&parsed_tokens, input, shell);
		post_init_tokens(parsed_tokens); // add to parse
		shell.tokens = parsed_tokens;
		if (ft_strcmp(input, "$?") == 0)
			printf("%d\n", shell.question);
		else
			execution(&shell);
        add_history(input);
		free_tokens(&parsed_tokens);
	}
	free(__environ);
	__environ = arr;
	return (1);
}