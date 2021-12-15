/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:57:07 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/15 00:23:17 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

static void	print_command_error(char **cmd)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	split_free(cmd);
}

static void	exit_with_err_status(char **cmd)
{
	print_command_error(cmd);
	exit(ERROR_STATUS);
}

static char	*create_path(char **cmd, char **envp)
{
	int		i;
	char	*path;
	char	*half_path;
	char	**paths;

	paths = find_paths(envp);
	if (paths == NULL)
		exit_with_err_status(cmd);
	i = -1;
	while (paths[++i] != NULL)
	{
		half_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(half_path, cmd[0]);
		free(half_path);
		if (access(path, 1) == 0)
			return (return_path(paths, &path));
		free(path);
	}
	split_free(paths);
	if (access(cmd[0], 1) == 0)
		return (cmd[0]);
	print_command_error(cmd);
	exit(ERROR_STATUS);
}

void	simple_cmd(char **argv)
{
	char	*path;

	path = create_path(argv, __environ);
	g_is_tricky.g_ret = execve(path, argv, __environ);
	if (g_is_tricky.g_ret == -1)
	{
		perror("minishell");
		g_is_tricky.g_ret = ERROR_STATUS;
		exit(ERROR_STATUS);
	}
}
