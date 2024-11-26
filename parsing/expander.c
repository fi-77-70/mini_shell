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
	if(var)
		i = ft_strlen(var);
	final = (char *)malloc(sizeof(char) * (ft_strlen(str) + i - ft_strlen(var_name)) + 1);
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
			if(str[i] == '$')
				i++;
			while (str[i] != ' ' && str[i] != '"' && str[i] != '$' && str[i] != 39 && str[i])
				i++;
			expanded = 1;
			if(!var)
				break;
			while (var[a])
				final[j++] = var[a++];
		}
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

	if(!env_var)
		return(NULL);
	i = 0;
	while(env_var[i] != ' ' && env_var[i] != '"' && env_var[i] != 39 && env_var[i] != '$' && env_var[i])
		i++;
	var = (char *)malloc(sizeof(char) * i + 1);
	if (!var)
		return (NULL);
	i = 0;
	while(env_var[i] != ' ' && env_var[i] != '"' && env_var[i] != 39 && env_var[i] != '$' && env_var[i])
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
	var_name = get_var_name(str + i);
	expanded = env_get(var_name, menu);
	i--;
	return (ft_final_expand(str, expanded, var_name, i));
}

void	expand(t_args **args, t_menu *menu)
{
	int		i;
	int		quoted;
	t_args	*temp;
	t_args  *msh;

	temp = NULL;
	temp = *args;
	msh = temp;
	quoted = -1;
	while(temp)
	{
		i = -1;
		while(temp->token[++i])
		{
			if(temp->token[i] == '"')
				quoted *= -1;
			if (temp->token[i] == 39 && quoted == -1)
			{
				i++;
				while (temp->token[i] != 39 && temp->token[i])
					i++;
			}
			if (temp->token[i] == '$' && temp->token[i + 1] && temp->token[i + 1] != '~' && temp->token[i + 1] != '$' && temp->token[i + 1] != '?')
				temp->token = ft_expander(temp->token, i, menu);
			if (!temp->token[i])
				break ;
		}
		temp = temp->next;
	}
  *args = msh;
}
