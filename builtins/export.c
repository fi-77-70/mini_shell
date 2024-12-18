#include "../minishell.h"

int	ft_export(t_cmds *cmds, t_menu *menu)
{
	int	i;

	i = 1;
	if (!cmds->args[1])
	{
		print_env(menu);
		return (menu->return_code = 0, 0);
	}
	while (cmds->args[i])
	{
		if (handle_export_arg(cmds->args[i], menu))
			return (menu->return_code = 1, 1);
		i++;
	}
	return (menu->return_code = 0, 0);
}

int	handle_export_arg(char *arg, t_menu *menu)
{
	int		index;
	char	*key;
	char	*value;
	char	*new_entry;

	if (!parse_export_input(arg))
		return (menu->return_code = 1, write_error_message("export: not valid\n"), 1);
	find_key_value(arg, &key, &value);
	if (!value)
		new_entry = ft_strjoin(key, "=");
	else
		new_entry = ft_strjoin3(key, '=', value);
	index = find_env_index(menu->env, key);
	if (index != -1)
	{
		free(menu->env[index]);
		menu->env[index] = new_entry;
	}
	else
		menu->env = create_env(menu->env, new_entry);
	free(key);
	free(value);
	return (menu->return_code = 0, 0);
}

void	print_env(t_menu *menu)
{
	int	i;

	i = 0;
	if (!menu || !menu->env)
	{
		write_error_message("export: Failed to obtain vars\n");
		return ;
	}
	while (menu->env[i])
	{
		if (ft_strchr(menu->env[i], '='))
			printf("declare -x %s\n", menu->env[i]);
		i++;
	}
	menu->return_code = 0;
}

/* int	parse_export_input(const char *input)
{
	int	i;
	int	equal_sign;

	i = 0;
	equal_sign = 0;
	if (!input || input[0] == '\0'
		|| (!(ft_isalpha(input[i])) && input[i] != '_'))
		return (0);
	i++;
	while (input[i])
	{
		if (input[i] == '=')
		{
			equal_sign++;
			if (equal_sign > 1)
				return (0);
		}
		else if (!ft_isalnum(input[i]) && input[i] != '_')
			return (0);
		i++;
	}
	return (1);
} */

int	parse_export_input(const char *input)
{
	int	i;
	int	equal_sign;

	i = 0;
	equal_sign = 0;

	if (!input || input[0] == '\0'
		|| (!(ft_isalpha(input[i])) && input[i] != '_'))
		return (0);
	i++;
	while (input[i] && input[i] != '=')
	{
		if (input[i] == ' ' || input[i] == '\t')
			return (0);
		i++;
	}
	return (1);
}

void	find_key_value(char *input, char **key, char **value)
{
	int	pos;

	if (!input || !key || !value)
		return ;
	pos = 0;
	while (input[pos] && input[pos] != '=')
		pos++;
	if (input[pos] == '\0')
	{
		*key = ft_strdup(input);
		*value = NULL;
	}
	else
	{
		*key = ft_substr(input, 0, pos);
		*value = ft_strdup(&input[pos + 1]);
	}
}
