#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

void	split_free(char **paths);
char	**find_paths(char **envp);
void	wrong_command(char **cmd);
char	*create_path(char **cmd, char **envp);

#endif