#include "../includes/minishell.h"

static void exec(char *cmd, char **env){

	char **cat;
	cat = malloc(sizeof(char *) * 2); cat[0] = ft_strdup("/bin/cat"); cat[1] = NULL;
		
	char **ls;
	ls = malloc(sizeof(char *) * 2); ls[0] = ft_strdup("/bin/ls"); ls[1] = NULL;

	if (strcmp("cat", cmd) == 0)
		execve(cat[0], cat, env);
	if (strcmp("ls", cmd) == 0)
	execve(ls[0], ls, env);
}

void execute_test_pipe(char **env)
{
	int		end[2];
	pid_t	parent_cat;
	pid_t	parent_ls;
	
	pipe(end);
	
	parent_cat = fork();
	if (parent_cat == 0){
		dup2(end[1], STDOUT);
		close(end[0]);
		exec("cat", env);
	}

	parent_ls = fork();
	if (parent_ls == 0){
		dup2(end[0], STDIN);
		close(end[1]);
		exec("ls", env);
	}

	close(end[0]);
	close(end[1]);
	waitpid(parent_cat, NULL, 0);
	waitpid(parent_ls, NULL, 0);
}