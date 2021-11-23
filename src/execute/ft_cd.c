#include "../parser.h"
#include "../libft/libft.h"

int	print_cd_error(char *str, int type)
{
	if (type == 1)
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
	}
	return (1);
}

void	update_oldpwd(char *oldpwd)
{
	int		i;
	char	*temp;

	if (getenv("OLDPWD"))
	{
		i = 0;
		while (__environ[i])
		{
			if (ft_strncmp("OLDPWD=", __environ[i], 7) == 0)
			{
				free(__environ[i]);
				__environ[i] = ft_strjoin("OLDPWD=", oldpwd);
				free(oldpwd);
				return ;
			}
			i++;
		}
	}
	temp = ft_strjoin("OLDPWD=", oldpwd);
	__environ = realloc_environ(1, temp);
	free(oldpwd);
	free(temp);
}

int	ft_cd(t_token *token)
{
	int		ret;
	char	*new_dir;
	char	*oldpwd;
	
	if (token && token->next && token->next->type == ARG)
		ret = print_cd_error(token->str, 1);
	else if (token == NULL || (token && token->type != ARG))
	{
		new_dir = getenv("HOME");
		if (new_dir)
		{
			oldpwd = getcwd(NULL, 0);
			ret = chdir(new_dir);
			if (ret == 0)
				update_oldpwd(oldpwd);
			else
			{
				ret = print_cd_error(new_dir, 2);
				free(oldpwd);
			}
		}
		else
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else if (ft_strcmp(token->str, "-") == 0)
	{
		new_dir = getenv("OLDPWD");
		if (new_dir)
		{
			oldpwd = getcwd(NULL, 0);
			ret = chdir(new_dir);
			if (ret == 0)
				update_oldpwd(oldpwd);
			else
			{
				ret = print_cd_error(new_dir, 2);
				free(oldpwd);
			}
		}
		else
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (1);
		}
	}
	else
	{
		oldpwd = getcwd(NULL, 0);
		ret = chdir(token->str);
		if (ret == 0)
			update_oldpwd(oldpwd);
		else
		{
			ret = print_cd_error(token->str, 2);
			free(oldpwd);
		}
	}
	return(ret);
}
