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
void execute_test_pipe_3(char **env)
{
	int		p1[2];
	int		p2[2];
	int		p3[2];
	pid_t	parent_cat;
	pid_t	parent_cat2;
	pid_t	parent_cat3;
	pid_t	parent_ls;
	
	pipe(p1);
	parent_cat = fork();
	if (parent_cat == 0){
		dup2(p1[1], STDOUT);
		close(p1[0]);
		exec("cat", env);
	}

	pipe(p2);
	parent_cat2 = fork();
	if (parent_cat2 == 0){
		dup2(p1[0], STDIN);
		close(p1[1]);

		dup2(p2[1], STDOUT);
		close(p2[0]);
		exec("cat", env);
	}
	close(p1[0]);
	close(p1[1]);

	pipe(p3);
	parent_cat3 = fork();
	if (parent_cat3 == 0)
	{
		dup2(p2[0], STDIN);
		close(p2[1]);

		dup2(p3[1], STDOUT);
		close(p3[0]);
		exec("cat", env);
	}
	close(p2[1]);
	close(p2[0]);

	parent_ls = fork();
	if (parent_ls == 0){
		dup2(p3[0], STDIN);
		close(p3[0]);
		exec("ls", env);
	}
	close(p3[1]);
	close(p3[0]);
	//close(p2[1]);
	//close(p2[0]);
	//close(p1[0]);
	//close(p1[1]);
	wait(0);
	wait(0);
	wait(0);
	wait(0);
}