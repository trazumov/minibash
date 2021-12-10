/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlatashi <mlatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:41:51 by mlatashi          #+#    #+#             */
/*   Updated: 2021/12/10 17:52:42 by mlatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	update_pwd(char *pwd)
{
	int		i;

	if (getenv("PWD"))
	{
		i = 0;
		while (__environ[i])
		{
			if (ft_strncmp("PWD=", __environ[i], 4) == 0)
			{
				free(__environ[i]);
				__environ[i] = ft_strjoin("PWD=", pwd);
				free(pwd);
				return ;
			}
			i++;
		}
	}
	else
		free(pwd);
}

void	update_oldpwd(char *oldpwd)
{
	int		i;
	char	*temp;

	update_pwd(getcwd(NULL, 0));
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

int	change_dir_to_home_or_oldpwd(char *var)
{
	int		ret;
	char	*new_dir;
	char	*oldpwd;

	new_dir = getenv(var);
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
		return (ret);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(" not set", 2);
		return (1);
	}
}

int	ft_cd(t_token *token)
{
	int		ret;
	char	*oldpwd;

	if (token && token->next && token->next->type == ARG)
		ret = print_cd_error(token->str, 1);
	else if (token == NULL || (token && token->type != ARG))
		ret = change_dir_to_home_or_oldpwd("HOME");
	else if (ft_strcmp(token->str, "-") == 0)
		ret = change_dir_to_home_or_oldpwd("OLDPWD");
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
	return (ret);
}
