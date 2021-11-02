#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	preparser(char *str)
{
	int	i;
	int	quotes;
	int	dbl_quotes;

	i = 0;
	quotes = 0;
	dbl_quotes = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !quotes && !dbl_quotes)
			quotes = 1;
		else if (str[i] == '"' && !quotes && !dbl_quotes)
			dbl_quotes = 1;
		else if (str[i] == '\'' && quotes)
			quotes = 0;
		else if (str[i] == '"' && dbl_quotes)
			dbl_quotes = 0;
		else if (str[i] == ';' && !quotes && !dbl_quotes)
			return (1);
		else if (str[i] == '|' && !quotes && !dbl_quotes)
		{
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '|' || str[i] == '\0')
				return (1);
			i--;
		}
		i++;
	}
	if (quotes || dbl_quotes)
		return (1);
	return (0);
}

void	free_intermediate_strings(char *t, char *p_1, char *p_2, char *var)
{
	free(t);
	free(p_1);
	free(p_2);
	free(var);
}

void	remove_quotes(char *str, int start, int end)
{
	int	i;

	i = start;
	while (i < end - 1)
	{
		str[i] = str[i + 1];
		i++;
	}
	while (str[i + 2] != '\0')
	{
		str[i] = str[i + 2];
		i++;
	}
	str[i] = '\0';
}

char	*remove_invalid_var_name(char *str, char *var_name, int *start)
{
	int	i;
	int	len;

	len = ft_strlen(var_name) + 1;
	i = *start;
	while (str[i + len] != '\0')
	{
		str[i] = str[i + len];
		i++;
	}
	str[i] = '\0';
	*start -= 1;
	free(var_name);
	return (str);
}

char	*handle_quotes(char *str, int *start)
{
	int	end;

	end = *start + 1;
	while (str[end] != '\'')
		end++;
	remove_quotes(str, *start, end);
	*start = end - 2;
	return (str);
}

char	*handle_bucks(char *str, int *start)
{
	int		i;
	char	*var_name;
	char	*var_value;
	char	*temp;
	char	*part_1;
	char	*part_2;

	i = *start + 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i == *start + 1)
		return (str);
	var_name = ft_substr(str, *start + 1, i - *start - 1);
	var_value = getenv(var_name);
	if (var_value == NULL)
		return (remove_invalid_var_name(str, var_name, start));
	part_1 = ft_substr(str, 0, *start);
	part_2 = ft_substr(str, i, ft_strlen(str) - i);
	temp = ft_strjoin(part_1, var_value);
	free(str);
	str = ft_strjoin(temp, part_2);
	*start = ft_strlen(temp) - 1;
	free_intermediate_strings(temp, part_1, part_2, var_name);
	return (str);
}

char	*handle_double_quotes(char *str, int *start)
{
	int		end;

	end = *start + 1;
	while (str[end] != '"')
	{
		if (str[end] == '$')
			str = handle_bucks(str, &end);
		end++;
	}
	remove_quotes(str, *start, end);
	*start = end - 2;
	return (str);
}

char	*parser(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			str = handle_quotes(str, &i);
		else if (str[i] == '"')
			str = handle_double_quotes(str, &i);
		else if (str[i] == '$')
			str = handle_bucks(str, &i);
		i++;
	}
	return (str);
}

int	main(void)
{
	char	*str;

	str = readline(NULL);
	if (preparser(str))
	{
		free(str);
		printf("Error\n");
		return (0);
	}
	str = parser(str);
	printf("%s\n", str);
	free(str);
}
