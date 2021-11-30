#include "../includes/minishell.h"

static int ex_token(t_minishell *shell, t_token *token)
{
	if (token->type == CMD)
		execv_cmd(shell, get_prev_token(token));
	else
		return execute_builtin(shell, token);
	return 0;
}

int is_first_pipe(t_token *token)
{
	t_token *tmp = token->prev;

	while (tmp)
	{
		if (tmp->type == PIPE)
			return FALSE;
		tmp = tmp->prev;
	}
	return TRUE;
}

int is_mid_pipe(t_token *token)
{
	t_token *next = token->next;
	t_token *prev = token->prev;
	int		res = 0;

	while (next)
	{
		if (next->type == PIPE)
		{
			res++; break;
		}
		next = next->next;
	}
	while (prev)
	{
		if (prev->type == PIPE)
		{
			res++; break;
		}
		prev = prev->prev;
	}
	if (res == 2)
		return TRUE;
	return FALSE;
}

int is_last_pipe(t_token *token)
{
	t_token *tmp = token->next;

	while (tmp)
	{
		if (tmp->type == PIPE)
			return FALSE;
		tmp = tmp->next;
	}
	return TRUE;
}

void first_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;

	if (pipe(shell->fds[fd]) != 0)
		ft_putstr_fd("Pipe error\n", 2);
	parent = fork();
	struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == -1)
		ft_putstr_fd("Fork error\n", 2);
	if (parent == 0)
	{
		dup2(shell->fds[fd][1], STDOUT);
		close(shell->fds[fd][0]);
		if (get_prev_token(token)->type == CMD)
			execv_cmd(shell, get_prev_token(token));
		else
		{
			shell->ret = (execute_builtin(shell, get_prev_token(token)));
			exit (shell->ret);
		}
	}
}

void mid_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;

	if (pipe(shell->fds[fd]) != 0)
		ft_putstr_fd("Pipe error\n", 2);
	parent = fork();
	struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == -1)
		ft_putstr_fd("Fork error\n", 2);
	if (parent == 0)
	{
		dup2(shell->fds[fd - 1][0], STDIN);
		close(shell->fds[fd - 1][1]);
		dup2(shell->fds[fd][1], STDOUT);
		close(shell->fds[fd][0]);
		if (get_prev_token(token)->type == CMD)
			execv_cmd(shell, get_prev_token(token));
		else
		{
			shell->ret = (execute_builtin(shell, get_prev_token(token)));
			exit (shell->ret);
		}
	}
	close(shell->fds[fd - 1][0]);
	close(shell->fds[fd - 1][1]);
}

int the_only_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t 	parent;
	pid_t 	cmd;
	
	if (pipe(shell->fds[0]) == -1)
		ft_putstr_fd("Pipe error\n", 2);
	t_token *dbg = get_prev_token(token);
	parent = fork();
	struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == 0)
	{
		dup2(shell->fds[0][1], STDOUT);
		close(shell->fds[0][0]);
		if (get_prev_token(token)->type == CMD)
			execv_cmd(shell, get_prev_token(token));
		else
		{
			shell->ret = (execute_builtin(shell, get_prev_token(token)));
			exit (shell->ret);
		}
	}
	cmd = fork();
	struct_pid_add(&shell->childs, struct_pid_new(cmd));
	if (cmd == 0)
	{
		dup2(shell->fds[0][0], STDIN);
		close(shell->fds[0][1]);
		if (token->next->type == CMD)
			execv_cmd(shell, token->next);
		else
		{
			shell->ret = (execute_builtin(shell, token->next));
			exit (shell->ret);
		}
	}
	close(shell->fds[0][0]);
	close(shell->fds[0][1]);
	return 0;
}

void last_pipe(t_minishell *shell, t_token *token, int fd)
{
	pid_t	parent;
	pid_t	cmd;

	if (pipe(shell->fds[fd]) != 0)
		ft_putstr_fd("Pipe error\n", 2);
	parent = fork();
	struct_pid_add(&shell->childs, struct_pid_new(parent));
	if (parent == -1)
		ft_putstr_fd("Fork error\n", 2);
	if (parent == 0)
	{
		dup2(shell->fds[fd - 1][0], STDIN); // читаем из предыдущего
		close(shell->fds[fd - 1][1]);

		dup2(shell->fds[fd][1], STDOUT); // пишем в последний pipe
		close(shell->fds[fd][0]);

		if (get_prev_token(token)->type == CMD)
			execv_cmd(shell, get_prev_token(token));
		else
		{
			shell->ret = (execute_builtin(shell, get_prev_token(token)));
			exit (shell->ret);
		}
	}
	close(shell->fds[fd - 1][0]);
	close(shell->fds[fd - 1][1]);
	cmd = fork();
	struct_pid_add(&shell->childs, struct_pid_new(cmd));
	if (cmd == -1)
		ft_putstr_fd("Fork error\n", 2);
	if (cmd == 0)
	{
		dup2(shell->fds[fd][0], STDIN);
		close(shell->fds[fd][1]);

		if (token->next->type == CMD)
			execv_cmd(shell, token->next);
		else
		{
			shell->ret = (execute_builtin(shell, token->next));
			exit (shell->ret);
		}
	}
	close(shell->fds[fd][0]);
	close(shell->fds[fd][1]);
	
}