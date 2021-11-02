#include "../../includes/minishell.h"


// check if malloc OK
int	init_env(t_minishell *shell, char **env_export)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(env));
	if (!env)
		return (1);
	env->str = ft_strdup(env_export[0]);
	env->next = NULL;
	shell->env = env;
	i = 1;
	while (env_export && env_export[i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (1);
		new->str = ft_strdup(env_export[i]);
		if (!new)
			return (1);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}