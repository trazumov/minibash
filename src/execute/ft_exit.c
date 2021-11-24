#include "../parser.h"
#include "../libft/libft.h"

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_token *token)
{
	unsigned int	ret;

	ft_putendl_fd("exit", 2);
	if (token && ft_is_numeric(token->str) == 0)
	{
		ret = -1;//
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->str, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (token && token->next)
	{
		ret = -1; //
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (token)
		ret = ft_atoi(token->str);
	else
		ret = 0;
	return (ret);
}
