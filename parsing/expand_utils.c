#include "../minishell.h"

char	*get_env_value(char *str)
{
	int		a;
	int		i;
	char	*final;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	final = (char *)malloc(sizeof(char) * ft_strlen(str + i));
	if (!final)
		return (NULL);
	a = 0;
	while (str[++i])
		final[a++] = str[i];
	final[a] = 0;
	return (final);
}

int	strclen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*env_get(char *name, t_menu *menu)
{
	int i;
	int bytes;
	char **temp;

	if (!name)
		return (NULL);
	if (!ft_strcmp(name, "$"))
		return (ft_itoa(pid_get(menu)));
	i = -1;
	temp = menu->env;
	while (temp[++i])
	{
		if (ft_strclen(temp[i], '=') == (int)ft_strlen(name))
			bytes = ft_strclen(temp[i], '=');
		else
			bytes = ft_strlen(name);
		if (!ft_strncmp(temp[i], name, bytes) && temp[i][bytes] == '=')
			return (get_env_value(temp[i]));
	}
	return (NULL);
}