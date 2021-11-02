#include "pipex_bonus.h"
#include "../libft/libft.h"

void	create_tmp_file(char **argv)
{
	int		in;
	char	*line;

	in = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (in < 0 || read(in, 0, 0) < 0)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("heredoc> ", 0);
	while (get_next_line(0, &line))
	{
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2]) + 1) == 0)
			break ;
		ft_putendl_fd(line, in);
		free(line);
		ft_putstr_fd("heredoc> ", 0);
	}
	free(line);
	close(in);
}

void	exec_here_cmd1(char **argv, char **envp, int fd[][2])
{
	char	**options;
	char	*path;
	int		in;

	dup2(fd[0][1], 1);
	close_fd(argv, fd, 6);
	create_tmp_file(argv);
	in = open("tmp", O_RDONLY);
	if (in < 0 || read(in, 0, 0) < 0)
	{
		perror("tmp");
		exit(EXIT_FAILURE);
	}
	dup2(in, 0);
	close(in);
	options = ft_split(argv[3], ' ');
	path = create_path(options[0], envp);
	if (execve(path, options, envp) == -1)
	{
		perror(path);
		split_free(options);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	exec_here_cmd2(char **argv, char **envp, int fd[][2], int i)
{
	char	**options;
	char	*path;
	int		out;

	dup2(fd[i - 1][0], 0);
	close_fd(argv, fd, 6);
	out = open(argv[i + 4], O_RDWR | O_CREAT | O_APPEND, 0664);
	if (out < 0)
	{
		perror(argv[i + 4]);
		exit(EXIT_FAILURE);
	}
	dup2(out, 1);
	close(out);
	options = ft_split(argv[i + 3], ' ');
	path = create_path(options[0], envp);
	if (execve(path, options, envp) == -1)
	{
		perror(path);
		split_free(options);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	exec_here_cmd(char **argv, char **envp, int fd[][2], int i)
{
	char	**options;
	char	*path;

	dup2(fd[i - 1][0], 0);
	dup2(fd[i][1], 1);
	close_fd(argv, fd, 6);
	options = ft_split(argv[i + 3], ' ');
	path = create_path(options[0], envp);
	if (execve(path, options, envp) == -1)
	{
		perror(path);
		split_free(options);
		free(path);
		exit(EXIT_FAILURE);
	}
}

int	here_doc(int argc, char **argv, char **envp)
{
	int		i;
	int		fd[OPEN_MAX][2];
	pid_t	pid[OPEN_MAX];

	i = -1;
	while (++i < argc - 5)
	{
		if (pipe(fd[i]) == -1)
			return (2);
	}
	i = -1;
	while (++i < argc - 4)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (3);
		if (pid[i] == 0 && i == 0)
			exec_here_cmd1(argv, envp, fd);
		else if (pid[i] == 0 && i == argc - 5)
			exec_here_cmd2(argv, envp, fd, i);
		else if (pid[i] == 0)
			exec_here_cmd(argv, envp, fd, i);
	}
	close_fd(argv, fd, 6);
	return (waitpid_at_exit(pid, argc));
}
