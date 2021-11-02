#include "pipex_bonus.h"
#include "../libft/libft.h"

void	execute_cmd1(char **argv, char **envp, int fd[][2])
{
	char	**options;
	char	*path;
	int		in;

	dup2(fd[0][1], 1);
	close_fd(argv, fd, 5);
	in = open(argv[1], O_RDONLY);
	if (in < 0 || read(in, 0, 0) < 0)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	dup2(in, 0);
	close(in);
	options = ft_split(argv[2], ' ');
	path = create_path(options[0], envp);
	if (execve(path, options, envp) == -1)
	{
		perror(path);
		split_free(options);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	execute_cmd2(char **argv, char **envp, int fd[][2], int i)
{
	char	**options;
	char	*path;
	int		out;

	dup2(fd[i - 1][0], 0);
	close_fd(argv, fd, 5);
	out = open(argv[i + 3], O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (out < 0)
	{
		perror(argv[i + 3]);
		exit(EXIT_FAILURE);
	}
	dup2(out, 1);
	close(out);
	options = ft_split(argv[i + 2], ' ');
	path = create_path(options[0], envp);
	if (execve(path, options, envp) == -1)
	{
		perror(path);
		split_free(options);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	execute_cmd(char **argv, char **envp, int fd[][2], int i)
{
	char	**options;
	char	*path;

	dup2(fd[i - 1][0], 0);
	dup2(fd[i][1], 1);
	close_fd(argv, fd, 5);
	options = ft_split(argv[i + 2], ' ');
	path = create_path(options[0], envp);
	if (execve(path, options, envp) == -1)
	{
		perror(path);
		split_free(options);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	multipipe(int fd[][2], pid_t pid[], char **argv, char **envp)
{
	int	i;
	int	ct;

	ct = 0;
	while (argv[ct] != NULL)
		ct++;
	i = -1;
	while (++i < ct - 3)
	{
		pid[i] = fork();
		if (pid[i] == 0 && i == 0)
			execute_cmd1(argv, envp, fd);
		else if (pid[i] == 0 && i == ct - 4)
			execute_cmd2(argv, envp, fd, i);
		else if (pid[i] == 0)
			execute_cmd(argv, envp, fd, i);
	}
	close_fd(argv, fd, 5);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		fd[OPEN_MAX][2];
	pid_t	pid[OPEN_MAX];

	if (argc < 5)
	{
		ft_putstr_fd("Incorrect number of arguments\n", 2);
		return (1);
	}
	if (argc > 1 && ft_strncmp(argv[1], "here_doc", 9) == 0)
		return (here_doc(argc, argv, envp));
	i = -1;
	while (++i < argc - 4)
	{
		if (pipe(fd[i]) == -1)
			return (2);
	}
	multipipe(fd, pid, argv, envp);
	i = -1;
	while (++i < argc - 3)
		waitpid(pid[i], NULL, 0);
}
