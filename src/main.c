#include "../includes/minishell.h"

//int	main(int argc, char **argv, char **envp)
int	main(void)
{
	t_minishell shell;
	char		*input = NULL;

	shell.exit = FALSE;
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	rl_catch_signals = 0;
	while (shell.exit != TRUE)
	{
		g_signal = 0;
		input = readline("minibash >");
		if (input == NULL)
		{
			on_eof(&shell);
			break ;
		}
		if (ft_strcmp(input, "exit"))
			shell.exit = TRUE;
        add_history(input);
		free(input);
	}
	return (1);
}