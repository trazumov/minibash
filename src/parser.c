#include "../includes/minishell.h"

void	print_error(char *str)
{
	free(str);
	printf("Error\n");
	exit(EXIT_FAILURE);
}


int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}


int	ft_issep(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13) || c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	handle_pipe(char *str, int i, int *sep_ct)
{
	i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|' || str[i] == '\0')
		print_error(str);
	(*sep_ct) += 2;
	return (i);
}

int	handle_redirection(char *str, int i, int *sep_ct)
{
	i++;
	if (str[i] == str[i - 1])
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (ft_issep(str[i]) || str[i] == '\0')
		print_error(str);
	(*sep_ct) += 2;
	return (i);
}

int	handle_sep(char *str, int i, int *sep_ct)
{
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		i = handle_pipe(str, i, sep_ct);
	else if (str[i] == '>' || str[i] == '<')
		i = handle_redirection(str, i, sep_ct);
	else if (str[i] != '\0')
		(*sep_ct)++;
	return (i - 1);
}

int	check_leading_pipe(char *str, int *sep_ct)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		print_error(str);
	// else if (str[i] == '\0')
	// 	*sep_ct = -1;
	(void)sep_ct;
	return (i);
}

void	preparser(char *str, int *sep_ct)
{
	int	i;
	int	quotes;
	int	dbl_quotes;

	quotes = 0;
	dbl_quotes = 0;
	i = check_leading_pipe(str, sep_ct);
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
		else if (ft_issep(str[i]) && !quotes && !dbl_quotes)
			i = handle_sep(str, i, sep_ct);
		i++;
	}
	if (quotes || dbl_quotes)
		print_error(str);
}

void	free_intermediate_strings(char *temp, char *part_1, char *part_2)
{
	free(temp);
	free(part_1);
	free(part_2);
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

void	replace_bucks(char *str, int i, int *start, char *var_value)
{
	char	*temp;
	char	*part_1;
	char	*part_2;
	
	part_1 = ft_substr(str, 0, *start);
	part_2 = ft_substr(str, i, ft_strlen(str) - i);
	temp = ft_strjoin(part_1, var_value);
	free(str);
	str = ft_strjoin(temp, part_2);
	*start = ft_strlen(temp) - 1;
	free_intermediate_strings(temp, part_1, part_2);
}

char	*handle_bucks(char *str, int *start, t_minishell msh)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = *start + 1;
	if (str[i] == '?')
	{
		var_value = ft_itoa(msh.question);
		replace_bucks(str, i + 1, start, var_value);
		free(var_value);
	}
	else
	{
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		if (i == *start + 1)
			return (str);
		var_name = ft_substr(str, *start + 1, i - *start - 1);
		var_value = getenv(var_name);
		if (var_value == NULL)
			return (remove_invalid_var_name(str, var_name, start));
		replace_bucks(str, i, start, var_value);
		free(var_name);
	}
	return (str);
}

char	*handle_double_quotes(char *str, int *start, t_minishell msh)
{
	int		end;

	end = *start + 1;
	while (str[end] != '"')
	{
		if (str[end] == '$')
			str = handle_bucks(str, &end, msh);
		end++;
	}
	remove_quotes(str, *start, end);
	*start = end - 2;
	return (str);
}

char	*parser(char *str, char **array, int token_ct, t_minishell msh)
{
	int	i, j, last_space;

	i = 0;
	j = 0;
	while (ft_isspace(str[i]))
		i++;
	last_space = i;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			str = handle_quotes(str, &i);
		else if (str[i] == '"')
			str = handle_double_quotes(str, &i, msh);
		else if (str[i] == '$')
			str = handle_bucks(str, &i, msh);
		else if (ft_issep(str[i]))
		{
			array[j] = ft_substr(str, last_space, i - last_space);
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			{
				if (str[i] != '|' && (str[i + 1] == '>' || str[i + 1] == '<'))
					array[++j] = ft_substr(str, i++, 2);
				else
					array[++j] = ft_substr(str, i, 1);
				while (ft_isspace(str[++i]))
					continue ;
			}
			last_space = i;
			j++;
			i--;
		}
		i++;
	}
	if (str[last_space] != '\0')
		array[j] = ft_substr(str, last_space, i - last_space);
	else if (str[last_space] == '\0' && j < token_ct)
		array[j] = ft_substr(str, last_space, i - last_space);
	return (str);
}

char	*parse(t_token **token, char *str, t_minishell msh)
{
	char	**array;
	int		sep_ct;

	sep_ct = 0;
	preparser(str, &sep_ct);
	//printf("sep_ct = %d\n", sep_ct);
	array = malloc((sep_ct + 1) * sizeof(*array));
	str = parser(str, array, sep_ct + 1, msh);
	//printf("%s\n", str);
	//if (sep_ct != -1)
		create_tokens(token, array, sep_ct + 1);
	free(array);
	return (str);
}

int	get_env_size(char **arr)
{
	int		size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

char	**malloc_environ(void)
{
	int		size;
	int		i;
	char	**arr;

	size = get_env_size(__environ);
	arr = malloc(sizeof(char *) * (size + 1));
	i = -1;
	while (++i < size)
		arr[i] = ft_strdup(__environ[i]);
	arr[i] = NULL;
	return (arr);
}