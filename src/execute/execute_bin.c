/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svirgil <svirgil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:57:07 by svirgil           #+#    #+#             */
/*   Updated: 2021/12/10 19:27:07 by svirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_free(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

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
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

static void	print_command_error(char **cmd)
{
	ft_putstr_fd("minishell$: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
}

static char	*create_path(char **cmd, char **envp)
{
	int		i;
	char	*path;
	char	*half_path;
	char	**paths;

	paths = find_paths(envp);
	i = -1;
	while (paths[++i] != NULL)
	{
		half_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(half_path, cmd[0]);
		free(half_path);
		if (access(path, 1) == 0)
		{
			split_free(paths);
			return (path);
		}
		free(path);
	}
	split_free(paths);
	if (access(cmd[0], 1) == 0)
		return (cmd[0]);
	print_command_error(cmd);
	split_free(cmd);
	exit(1);
}

void	simple_cmd(t_minishell *shell, char **argv)
{
	char	*path;

	path = create_path(argv, __environ);
	if ((execve(path, argv, __environ)) == -1)
	{
		perror("minishell:");
		exit(1);
	}
	free(path);
}
