#include "../includes/minishell.h"

static void	split_free(char **paths)
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

static void	wrong_command(char **cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	split_free(cmd);
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
	wrong_command(cmd);
	exit(1);
}

static void exec_cmd(char **argv, char **envp, int fd[])
{
	char	**options;
	char	*path;

	options = ft_split(argv[0], ' ');
	path = create_path(options, envp);
	execve(path, options, envp);
}

void	execution(t_minishell *shell, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	//pipe(fd);
	pid1 = fork();
	if (pid1 == -1)
		return ;
	if (pid1 == 0)
		exec_cmd(shell->tokens->argv, envp, fd);
	//close(fd[0]);
	//close(fd[1]);
	waitpid(pid1, NULL, 0);
}