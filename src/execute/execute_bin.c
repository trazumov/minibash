#include "../../includes/minishell.h"

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
	//
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	split_free(cmd);
	//
	exit(1);
}

static char **copy_argv(char **from)
{
	int		size = 1;
	char	**res;
	int i = 0;

	while (from[i] != NULL)
	{
		size++;
		i++;
	}
	res = malloc(sizeof(char *) * size);
	i = 0;
	while (from[i] != NULL)
	{
		res[i] = ft_strdup(from[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void simple_cmd(char **argv)
{
	char 	*path;
	char	**new_argv;

	new_argv = copy_argv(argv);
	path = create_path(new_argv, __environ); // здесь изменяется new_argv ?
	if (execve(path, argv, __environ) == -1)
	{
		perror("Error at simple_cmd");
		free_char_list(new_argv);
		exit(1);
	}
}