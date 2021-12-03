#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

void	split_free(char **paths);
char	**find_paths(char **envp);
char	*create_path(char *cmd, char **envp);
void	close_fd(char **argv, int (*fd)[2], int std_argc);
int		waitpid_at_exit(pid_t pid[], int argc);
void	exec_here_cmd1(char **argv, char **envp, int fd[][2]);
void	exec_here_cmd2(char **argv, char **envp, int fd[][2], int i);
void	exec_here_cmd(char **argv, char **envp, int fd[][2], int i);
int		here_doc(int argc, char **argv, char **envp);
int		get_next_line(int fd, char **line);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char const *s2);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	gnl_strlen(const char *s);

#endif