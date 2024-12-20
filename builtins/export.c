/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:03:19 by pmachado          #+#    #+#             */
/*   Updated: 2024/12/20 17:56:31 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_cmds *cmds, t_menu *menu)
{
	int	i;

	i = 1;
	if (!cmds->args[1])
	{
		print_env(menu);
		if (menu->is_child)
			return (free_mid_process(menu), exit (1), 1);
		return (menu->return_code = 0, 0);
	}
	while (cmds->args[i])
	{
		if (handle_export_arg(cmds->args[i], menu))
		{
			if (menu->is_child)
				return (free_mid_process(menu), exit (1), 1);
			return (menu->return_code = 1, 1);
		}
		i++;
	}
	if (menu->is_child)
		return (free_mid_process(menu), exit (1), 1);
	return (menu->return_code = 0, 0);
}

void	sub_key_value(t_menu *menu, char *key, char *value)
{
	int		len;
	int		i;
	char	*temp;

	i = 0;
	len = ft_strlen(key);
	while (ft_strncmp(menu->env[i], key, len))
		i++;
	if (ft_strchr(menu->env[i], '='))
		menu->env[i] = ft_strjoin_free(menu->env[i], value);
	else
	{
		temp = menu->env[i];
		menu->env[i] = ft_strjoin3(menu->env[i], '=', value);
		free (temp);
	}
}

int	handle_export_arg(char *arg, t_menu *menu)
{
	int		index;
	char	*key;
	char	*value;
	char	*new_entry;

	if (!parse_export_input(arg))
		return (menu->return_code = 1,
			write_error_message("export: not a valid identifier\n"), 1);
	find_key_value(arg, &key, &value);
	if (key_exists(menu, key))
		return (sub_key_value(menu, key, value),
			free(key), free(value), menu->return_code = 0, 0);
	if (!value)
		new_entry = ft_strdup(key);
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
	return (free(key), free(value), menu->return_code = 0, 0);
}

int	parse_export_input(const char *input)
{
	int	i;

	i = 0;
	if (!input || input[0] == '\0'
		|| (!(ft_isalpha(input[i])) && input[i] != '_'))
		return (0);
	i++;
	while (input[i] && input[i] != '=')
	{
		if (!(ft_isalnum(input[i]) || input[i] == '_'))
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
