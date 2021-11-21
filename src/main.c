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
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_minishell	shell;
	t_token		*parsed_tokens = NULL;
	char		*input = NULL;
	
	g_return = 0;
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	while (shell.exit != TRUE)
	{
		init_shell(&shell);
		input = readline(shell.message);
		if (input == NULL)
		{
			on_eof(&shell);
			break ;
		}
		add_history(input);
		parse(&parsed_tokens, input);
		post_init_tokens(parsed_tokens);
		shell.tokens = parsed_tokens;
		if (ft_strcmp(input, "exit") == 0) // add additional write Exit / переписать
			shell.exit = TRUE;
		execution(&shell, envp);
        //add_history(input);
		//free(input);		input = NULL;
		free_tokens(&parsed_tokens);
	}
	return (1);
}