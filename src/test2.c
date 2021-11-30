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


// cat | cat | pipe
void execute_test_pipe_2(char **env)
{
	int		end[2];
	int		sec[2];
	pid_t	parent_cat;
	pid_t	parent_cat2;
	pid_t	parent_ls;
	
	pipe(end);
	
	parent_cat = fork();
	if (parent_cat == 0){
		dup2(end[1], STDOUT);
		close(end[0]);
		exec("cat", env);
	}

	pipe(sec);
	parent_cat2 = fork();
	if (parent_cat2 == 0){
		dup2(end[0], STDIN);
		close(end[1]);

		dup2(sec[1], STDOUT);
		close(sec[0]);
		exec("cat", env);
	}
	//close(end[0]);
	//close(end[1]);

	parent_ls = fork();
	if (parent_ls == 0){
		dup2(sec[0], STDIN);
		close(sec[0]); // 
		exec("ls", env);
	}
	close(sec[1]);
	close(sec[0]);
	close(end[0]);
	close(end[1]);
	wait(0);
	wait(0);
	wait(0);
	/*
	waitpid(parent_cat, NULL, 0);
	waitpid(parent_cat2, NULL, 0);
	waitpid(parent_ls, NULL, 0); */
}