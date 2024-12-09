#include "../minishell.h"

char	*ft_final_expand(char *str, char *var, char *var_name, int n)
{
	int		i;
	int		j;
	int		a;
	int		expanded;
	char	*final;

	i = 0;
	expanded = 0;
	if (var)
		i = ft_strlen(var);
	final = (char *)malloc(sizeof(char) * (ft_strlen(str) + (i * 2)
				- ft_strlen(var_name)) + 1);
	i = -1;
	j = 0;
	a = 0;
	while (str[++i])
	{
		while (i < n)
		{
			final[j++] = str[i];
			i++;
		}
		if (str[i] == '$' && expanded == 0)
		{
			i++;
			while (ft_isalnum(str[i]))
				i++;
			if (str[i] == '?')
				i++;
			expanded = 1;
			while (var && var[a])
			{
				final[j++] = 92;
				final[j++] = var[a++];
			}
		}
		if (str[i])
			final[j++] = str[i];
		if (!str[i])
			break ;
	}
	final[j] = 0;
	return (free(var_name), free(str), free(var), final);
}

char	*get_var_name(char *env_var)
{
	int		i;
	char	*var;

	if (!env_var)
		return (NULL);
	i = 0;
	while (ft_isalnum(env_var[i]))
		i++;
	var = (char *)malloc(sizeof(char) * i + 1);
	if (!var)
		return (NULL);
	i = 0;
	while (env_var[i] && ft_isalnum(env_var[i]))
	{
		var[i] = env_var[i];
		i++;
	}
	var[i] = 0;
	return (var);
}

char	*ft_expander(char *str, int i, t_menu *menu)
{
	char	*var_name;
	char	*expanded;

	i++;
	if (str[i] == '?')
	{
		var_name = ft_strdup("?");
		expanded = ft_itoa(menu->return_code);
	}
	else if (str[i] == '$')
	{
		var_name = ft_strdup("$");
		expanded = ft_itoa(pid_get(menu));
	}
	else
	{
		var_name = get_var_name(str + i);
		expanded = env_get(var_name, menu);
	}
	i--;
	return (ft_final_expand(str, expanded, var_name, i));
}
