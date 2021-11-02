#include "pipex.h"
#include "libft/libft.h"

void	execute_cmd1(char **argv, char **envp, int fd[])
{
	char	**options;
	char	*path;
	int		in;

	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	in = open(argv[1], O_RDONLY);
	if (in < 0 || read(in, 0, 0) < 0)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	dup2(in, 0);
	close(in);
	options = ft_split(argv[2], ' ');
	path = create_path(options, envp);
	if (execve(path, options, envp) == -1)
	{
		perror(path);
		split_free(options);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	execute_cmd2(char **argv, char **envp, int fd[])
{
	char	**options;
	char	*path;
	int		out;

	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (out < 0)
	{
		perror(argv[4]);
		exit(EXIT_FAILURE);
	}
	dup2(out, 1);
	close(out);
	options = ft_split(argv[3], ' ');
	path = create_path(options, envp);
	if (execve(path, options, envp) == -1)
	{
		perror(path);
		split_free(options);
		free(path);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	if (pipe(fd) == -1)
		return (2);
	pid1 = fork();
	if (pid1 == -1)
		return (3);
	else if (pid1 == 0)
		execute_cmd1(argv, envp, fd);
	pid2 = fork();
	if (pid2 == -1)
		return (4);
	if (pid2 == 0)
		execute_cmd2(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
