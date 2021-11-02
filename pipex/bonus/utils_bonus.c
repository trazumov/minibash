#include "pipex_bonus.h"
#include "../libft/libft.h"

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

char	**find_paths(char **envp)
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

char	*create_path(char *cmd, char **envp)
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
		path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(path, X_OK) == 0)
		{
			split_free(paths);
			return (path);
		}
		free(path);
	}
	split_free(paths);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	exit(EXIT_FAILURE);
}

void	close_fd(char **argv, int (*fd)[2], int std_argc)
{
	int	ct;

	ct = 0;
	while (argv[ct] != NULL)
		ct++;
	ct -= std_argc;
	while (ct >= 0)
	{
		close(fd[ct][0]);
		close(fd[ct][1]);
		ct--;
	}
}

int	waitpid_at_exit(pid_t pid[], int argc)
{
	int	i;

	i = -1;
	while (++i < argc - 4)
		waitpid(pid[i], NULL, 0);
	unlink("tmp");
	return (0);
}
