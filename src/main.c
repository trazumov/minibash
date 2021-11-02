#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell shell;
	char		*input;

	shell.exit = FALSE;
	while (shell.exit != TRUE)
	{
		//printf("minishell >:");
		init_env(&shell, envp);
		/*
		Обработка вводимых данных
		*/
		parser(&shell, input);
		input = readline(NULL);
		if (!input)
            break;
		if (ft_strcmp(input, "exit"))
			shell.exit = TRUE;
		if (ft_strcmp(input, "env"))
		{
			printf("%s\n", shell.env->str);
			printf("%s\n", shell.env->next->str);
		}
        add_history(input); // adding the previous input into history
		free(input);
	}
	return (1);
}