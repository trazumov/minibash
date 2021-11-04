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
		if (ft_strcmp(input, "exit"))
			shell.exit = TRUE;
        add_history(input);
		free(input);
	}
	free_data(&shell);
	return (1);
}