#include "../includes/minishell.h"

//int	main(int argc, char **argv, char **envp)
int	main(void)
{
	t_minishell shell;
	char		*input = NULL;

	shell.exit = FALSE;
	signal(SIGINT, ft_signal);
	while (shell.exit != TRUE)
	{
		g_signal = 0;
		input = readline("minibash >");
		if (!input)
            break ;
		if (ft_strcmp(input, "exit"))
			shell.exit = TRUE;
		// adding the previous input into history
		if (g_signal == 1)
		{
			g_signal = 0;
			continue ;
		}
        add_history(input);
		free(input);
	}
	return (1);
}