#include "../includes/minishell.h"

//int	main(int argc, char **argv, char **envp)
int	main(void)
{
	t_minishell shell;
	char		*input = NULL;

	init_shell(&shell);
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	while (shell.exit != TRUE)
	{
		input = readline(shell.message);
		if (input == NULL)
		{
			on_eof(&shell);
			break ;
		}
		// временная обмазка для тестирования
		t_token *tmp_token = create_tmp_token();
		shell.tokens = tmp_token;
		//
		if (ft_strcmp(input, "exit")) // add additional write
			shell.exit = TRUE;
		if (tmp_token != NULL)
			execution(&shell);
        add_history(input);
		free(input);
	}
	free_data(&shell);
	return (1);
}