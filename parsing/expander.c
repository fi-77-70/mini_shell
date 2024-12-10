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
	final = (char *)malloc(sizeof(char) * (ft_strlen(str) + (i * 2) - ft_strlen(var_name)) + 1);
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

	if(!env_var)
		return(NULL);
	i = 0;
	while(ft_isalnum(env_var[i]))
		i++;
	var = (char *)malloc(sizeof(char) * i + 1);
	if (!var)
		return (NULL);
	i = 0;
	while(env_var[i] && ft_isalnum(env_var[i]))
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

// void	expand(t_args **args, t_menu *menu)
// {
// 	int		i;
// 	int		quoted;
// 	t_args	*temp;

// 	temp = NULL;
// 	temp = *args;
// 	quoted = -1;
// 	while(temp)
// 	{
// 		i = -1;
// 		while(temp->token[++i])
// 		{
// 			if(temp->token[i] == '"')
// 				quoted *= -1;
// 			if (temp->token[i] == 39 && quoted == -1)
// 			{
// 				i++;
// 				while (temp->token[i] != 39 && temp->token[i])
// 					i++;
// 			}
// 			if (temp->token[i] == '$' && temp->token[i + 1] && temp->token[i + 1] != '~' && temp->token[i + 1] != '"' && !is_white_space(temp->token[i + 1]))
// 				temp->token = ft_expander(temp->token, i, menu);
// 			if (!temp->token[i] && i == 0)
// 			{
// 				if (temp->next && temp->prev)
// 				{
// 					temp->prev->next = temp->next;
// 					temp->next->prev = temp->prev;
// 				}
// 				else if (temp->next)
// 				{
// 					*(menu->mshh) = temp->next;
// 					temp->next->prev = NULL;
// 				}
// 				else if (temp->prev)
// 					temp->prev->next = NULL;
// 				free(temp);
// 				temp = NULL;
// 				break;
// 			}
// 		}
// 		if (temp)
// 			temp = temp->next;
// 	}
// }
