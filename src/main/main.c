/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:40:27 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/14 21:36:42 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	post_init_tokens(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		tmp->skip = FALSE;
		if (tmp->type == CMD && ft_strcmp(tmp->str, "") == 0)
			tmp->skip = TRUE;
		tmp = tmp->next;
	}
}

static void	update_history(char *input)
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

static void	pre_init(t_minishell *shell, char ***arr)
{
	*arr = NULL;
	*arr = __environ;
	__environ = malloc_environ();
	shell->exit = FALSE;
	g_is_tricky.g_ret = 0;
	g_is_tricky.g_run = FALSE;
	g_is_tricky.g_ret = 0;
}

static int	main_cycle(\
t_minishell *shell, char **input, t_token **parsed_tokens, int first_call)
{
	init_shell(shell);
	if (shell->error)
		return (2);
	if (*input && !first_call)
		free(*input);
	if (!first_call)
		*input = readline(shell->message);
	if (ctrl_d(shell, *input))
	{
		free(shell->message);
		return (1);
	}
	update_history(*input);
	*input = parse(parsed_tokens, *input);
	if (*input == NULL)
	{
		free(shell->message);
		return (2);
	}
	post_init_tokens(*parsed_tokens);
	shell->tokens = *parsed_tokens;
	execution(shell);
	free_tokens(parsed_tokens);
	return (0);
}

int	main(void)
{
	t_minishell	shell;
	t_token		*parsed_tokens;
	char		*input;
	char		**arr;
	int			cycle;

	parsed_tokens = NULL;
	input = NULL;
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	rl_catch_signals = 0;
	input = readline("minishell$ ");
	pre_init(&shell, &arr);
	cycle = main_cycle(&shell, &input, &parsed_tokens, TRUE);
	while (shell.exit != TRUE)
	{
		cycle = main_cycle(&shell, &input, &parsed_tokens, FALSE);
		if (cycle == 1)
			break ;
		if (cycle == 2)
			continue ;
	}
	free_on_exit(&input);
	__environ = arr;
	return (g_is_tricky.g_ret);
}
