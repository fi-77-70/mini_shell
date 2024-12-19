#include "../minishell.h"

int	check_pipe_exist(char *str, int i)
{
	int	other_word;
	int	j;

	other_word = 0;
	j = i;
	while (str[i] && str[i] != '|')
	{
		if (str[i] == ' ')
			other_word = 1;
		if (other_word == 1 && ft_isalnum(str[i]))
			other_word = 2;
		if (other_word == 2)
			break;
		i++;
	}
	if (str[i] && str[i] == '|')
		return (1);
	i = j;
	other_word = 0;
	while (i >= 0 && str[i] && str[i] != '|')
	{
		if (str[i] == ' ')
			other_word = 1;
		if (other_word == 1 && ft_isalnum(str[i]))
			other_word = 2;
		if (other_word == 2)
			break;
		i--;
	}
	if (i >= 0 && str[i] && str[i] == '|')
		return (1);
	return (0);
}
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
			if (ft_isdigit(str[i]))
				i++;
			else
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
	if (var_name)
		free(var_name);
	return (free(str), free(var), final);
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
		if(!expanded)
			if (check_pipe_exist(str, i))
				expanded = ft_strdup(" ");
	}
	i--;
	return (ft_final_expand(str, expanded, var_name, i));
}
