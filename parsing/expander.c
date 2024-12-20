#include "../minishell.h"

char	*expand_variable(char *str, char *var, int *j)
{
	int	a;

	a = 0;
	while (var && var[a])
	{
		str[*j] = '\\';
		(*j)++;
		str[*j] = var[a++];
		(*j)++;
	}
	return (str);
}

void	final_1(char *str, int *i, int *expanded)
{
	*i += 1;
	if (ft_isdigit(str[*i]) || str[*i] == '$')
		*i += 1;
	else
		while (ft_isalnum(str[*i]))
			*i += 1;
	if (str[*i] == '?')
		*i += 1;
	*expanded = 1;
}

char	*ft_final_expand(char *str, char *var, char *var_name, int n)
{
	int		i;
	int		j;
	int		expanded;
	char	*final;

	i = 0;
	j = 0;
	expanded = 0;
	final = (char *)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(var) * 2
				- ft_strlen(var_name)) + 1);
	while (str[i])
	{
		if (i < n)
			final[j++] = str[i++];
		else if (str[i] == '$' && !expanded)
		{
			final_1(str, &i, &expanded);
			final = expand_variable(final, var, &j);
		}
		else
			final[j++] = str[i++];
	}
	return (free(str), free(var), free(var_name), final[j] = 0, final);
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
	if (ft_isdigit(env_var[0]))
		return (NULL);
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

	if (str[i] == '$')
		i++;
	if (str[i] == '?')
	{
		var_name = ft_strdup("?");
		expanded = ft_itoa(menu->return_code);
	}
	else if (str[i] == '$')
	{
		var_name = ft_strdup("$");
		expanded = ft_itoa(424242);
	}
	else
	{
		var_name = get_var_name(str + i);
		expanded = env_get(var_name, menu);
		if (!expanded)
			if (check_pipe_exist(str, i))
				expanded = ft_strdup(" ");
	}
	i--;
	return (ft_final_expand(str, expanded, var_name, i));
}
